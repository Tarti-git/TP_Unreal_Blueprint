// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Containers/UnrealString.h"
#include "PositionReport.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJET_UE4_BACHELORS_API UPositionReport : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPositionReport();


	static TArray<FString> strAnswers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	bool blnTest2;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite,Category = "Variables")
		bool blnTest;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//Hit component
	//Exemple Fct C++=>BluePrint
	UFUNCTION(BlueprintCallable, Category = "Hit component")
	FHitResult GetFirstPhysicsBodyInReach();
	

	UFUNCTION(BlueprintCallable, Category = "FLT")
	 static bool GetFloatByName(UObject* Target, FName VarName, float &outStr);

	UFUNCTION(BlueprintCallable, Category = "STR")
	static bool GetStrArrayByName(UObject* Target, FName VarName, TArray<FString> & outArrayOfStr);




private :
	//Instance get player controller
	class APlayerController *PController;


	TSubclassOf<class AActor> BP_SpawnCanvas;

	class UTextRenderComponent *TxtRender;


	

};
