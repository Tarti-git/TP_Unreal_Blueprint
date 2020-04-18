// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "EngineUtils.h"//iterator
#include "Components/TextRenderComponent.h"
#include "UObject/UnrealType.h"
#include "Templates/Casts.h"

TArray<FString> UPositionReport::strAnswers;

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	//UE_LOG(LogTemp, Warning, TEXT("Constructor"));
	// ...
	PController = NULL;


	static ConstructorHelpers::FClassFinder<AActor>BPCanavas(TEXT("/Game/BluePrints/BP/BP_Wall"));
	BP_SpawnCanvas = BPCanavas.Class;

	
	blnTest = true;
	blnTest2 = true;
	
	
	
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("BeginPlay"));



	if (ensure(BP_SpawnCanvas)) {
		
		//UE_LOG(LogTemp, Warning, TEXT("Reference Name : %s"), *BP_SpawnCanvas->GetName())

		for (TActorIterator<AActor> ActorItr(GetWorld());  ActorItr; ++ActorItr)
		{
			
			if (*ActorItr->GetClass()->GetName() == BP_SpawnCanvas->GetName()) {
					AActor *Act = *ActorItr;
				if (ensure(Act)) {
					//Debug
					//UE_LOG(LogTemp, Warning, TEXT("%s"), *Act->GetName())
					
					TxtRender = Act->FindComponentByClass<UTextRenderComponent>();
					if (ensure(TxtRender)) {
						//Debug
						//UE_LOG(LogTemp, Warning, TEXT("%s"), *TxtRender->GetName());
						TxtRender->SetText(FText::FromString(strAnswers[0]));
					

					}
						
				}
			}

		}
			
			
			
	}
	
	PController = GetWorld()->GetFirstPlayerController();

	if (ensure(PController)) {

		UE_LOG(LogTemp, Warning, TEXT("First PlayerController GetName(PlayerController) : %s "), *PController->GetName());

	}
	// ...

	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	FString FName = GetOwner()->GetName();
	FString FPosition = GetOwner()->GetTransform().GetLocation().ToString();
	FString FRotation = GetOwner()->GetTransform().GetRotation().ToString();

	
	//UE_LOG(LogTemp, Warning, TEXT("Player_ID :%s Position : %s Rotation : %s"),
	//	*FName, *FPosition, *FRotation);



	if (ensure(PController)) {
	
		if (PController->IsInputKeyDown(FKey("UP"))) {
			UE_LOG(LogTemp, Warning, TEXT("Touche UP "));
			TxtRender->SetText(FText::FromString(strAnswers[0]));
		}
		else if (PController->IsInputKeyDown(FKey("DOWN"))) {
			UE_LOG(LogTemp, Warning, TEXT("Touche DOWN "));
			TxtRender->SetText(FText::FromString(strAnswers[1]));
		}
		else if (PController->IsInputKeyDown(FKey("LEFT"))) {
			UE_LOG(LogTemp, Warning, TEXT("Touche LEFT "));
			TxtRender->SetText(FText::FromString(strAnswers[2]));

		}
		else if (PController->IsInputKeyDown(FKey("RIGHT"))) {
			UE_LOG(LogTemp, Warning, TEXT("Touche RIGHT "));
			TxtRender->SetText(FText::FromString(strAnswers[3]));
		}

	}
	
	
	//Debug
	/*for (int32 i = 0; i < strAnswers.Num(); i++)
		{
			UE_LOG(LogTemp, Warning, TEXT("Values strAnswers : %s"), *strAnswers[i]);
		}*/

	// ...
}
//Exemple Fct C++=>BluePrint
FHitResult UPositionReport::GetFirstPhysicsBodyInReach()
{
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	FVector PlayerViewPointVector;
	FRotator PlayerViewPointRotator;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointVector, PlayerViewPointRotator);

	FVector LineEnd= PlayerViewPointVector + PlayerViewPointRotator.Vector()*200.f;

	GetWorld()->LineTraceSingleByObjectType(Hit, PlayerViewPointVector,LineEnd ,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);

	return Hit;
}



bool UPositionReport::GetStrArrayByName(UObject * Target, FName VarName, TArray<FString> & outArrayOfStr)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		
		UArrayProperty* ArrayProp = FindField<UArrayProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
	
		if (ensure(ArrayProp)) {
			
			TArray<FString> *Dest = ArrayProp->ContainerPtrToValuePtr<TArray<FString>>(Target);
			/*TArray<FString>  tmps = *Dest;
			UE_LOG(LogTemp, Warning, TEXT("Val : %d"), tmps.Num());

			for (int32 i = 0; i < tmps.Num(); i++)
			{
				UE_LOG(LogTemp,Warning, TEXT("Values tmps : %s"),*tmps[i]);
			}*/
			outArrayOfStr = *Dest;
			strAnswers = *Dest;


			/*for (FString str : strAnswers)
			{
				UE_LOG(LogTemp, Warning, TEXT("Values tmps : %s"), *str);
			}
			*/
			
		
			
			return true;
		}
  	

		
	}
	return false;
	
}

bool UPositionReport::GetFloatByName(UObject * Target, FName VarName, float & outFloat)
{
	if (Target) //make sure Target was set in blueprints. 
	{
		float FoundFloat;
		UFloatProperty* FloatProp = FindField<UFloatProperty>(Target->GetClass(), VarName);  // try to find float property in Target named VarName
		if (FloatProp) //if we found variable
		{
			FoundFloat = FloatProp->GetPropertyValue_InContainer(Target);  // get the value from FloatProp
			//outFloat = FoundFloat;  // return float
			UE_LOG(LogTemp, Warning, TEXT("Valeur de test :  %f"), FoundFloat);
			return true; // we can return
		}
	}
	return false;
}