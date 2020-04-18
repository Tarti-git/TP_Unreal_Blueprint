#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CGrabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_UE4_BACHELORS_API UCGrabber : public UActorComponent
{
	GENERATED_BODY()
public:	
	// Sets default values for this component's properties
	UCGrabber();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;	
	FHitResult GetFirstPhysicsBodyInReach();
	void FindPhysicsHandleComponent();
	void SetInputComponent();
	void Handle();
	void Release();
	void Grab();
private :
	UPROPERTY(EditAnyWhere)
	float fltReach;
	UPhysicsHandleComponent *PhysicsHandle;
	UInputComponent *InputComponent;
	FVector GetReachLineStart();
	FVector GetReachLineEnd();
};
