#include "CGrabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "EngineUtils.h"
#include "CollisionQueryParams.h"
#include "DrawDebugHelpers.h"


/*
Description : Constructeur du Grabber
Input :
Output :
Note :
*/

UCGrabber::UCGrabber()
{
	PrimaryComponentTick.bCanEverTick = true;
	fltReach=200.f;
	PhysicsHandle = NULL;
	InputComponent = NULL;
}

/*
Description : Fonction qui commence au début
Input :
Output :
Note :
*/
void UCGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetInputComponent();
	
	if (InputComponent) {
			InputComponent->BindAction("Grab", IE_Pressed, this, &UCGrabber::Grab);
			InputComponent->BindAction("Grab", IE_Released, this, &UCGrabber::Release);
	}
}

/*
Description : fonction appellé à chaque tick
Input : DeltaTime,TickType, ThisFunctionTick
Output : ThisFunctionTick
Note :
*/
void UCGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
}


/*
Description : return le Hit result du component touché par le raytracing
Input :
Output :
Note :
*/
FHitResult UCGrabber::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;

	GetWorld()->LineTraceSingleByObjectType(Hit, GetReachLineStart(), GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
	return Hit;
}


/*
Description : recuperation du physichandle du blueprint
Input :
Output :
Note :
*/
void UCGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (ensure(PhysicsHandle))
		UE_LOG(LogTemp, Warning, TEXT("Component PhysicsHandle Find"));
}

void UCGrabber::SetInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (ensure(InputComponent)) {
		UE_LOG(LogTemp, Warning, TEXT("Component Input Find"));
	}
}

/*
Description : attrape le component de la scène
Input :
Output :
Note :
*/
void UCGrabber::Handle()
{
	FHitResult Hit=GetFirstPhysicsBodyInReach();
	UPrimitiveComponent *ComponentToGrab = Hit.GetComponent();
	AActor *ActorHit = Hit.GetActor();

	if (ActorHit) {
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation());
	}
}

void UCGrabber::Grab() {
	Handle();
}

/*
Description : setter du physichandle
Input :
Output :
Note :
*/

void UCGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

/*
Description : return le point de départ du linetrace
Input :
Output :
Note :
*/
FVector UCGrabber::GetReachLineStart()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);
	return PlayerViewPointVector;
}

/*
Description : return le point d'arrivé du linetrace
Input :
Output :
Note :
*/

FVector UCGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);
	FVector LineEnd=PlayerViewPointVector + PlayerViewPointRotator.Vector()*fltReach;
	return LineEnd;
}

