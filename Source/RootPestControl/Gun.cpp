// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
		
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (!OwnerPawn)
		return nullptr;

	return OwnerPawn->GetController();
}

bool AGun::GunTrace(FHitResult& OutHit, FVector& OutShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (!OwnerController)
		return false;
	
	FVector Location;
	FRotator Rotation;
	OwnerController->GetPlayerViewPoint(Location, Rotation);
	OutShotDirection = -Rotation.Vector();

	FVector End = Location + Rotation.Vector() * MaxRange;
		
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());
	//DrawDebugLine(GetWorld(), Location, End, FColor::Red, true);
	return GetWorld()->LineTraceSingleByChannel(OutHit, Location, End, ECC_GameTraceChannel1, Params);
}

void AGun::PullTrigger()
{
	// **** debug draw
	
	// APawn* OwnerPawn = Cast<APawn>(GetOwner());
	// if (!OwnerPawn) return;
	// AController* OwnerController = OwnerPawn->GetController();
	// if (!OwnerController) return;
	// FVector Location;
	// FRotator Rotation;
	// OwnerController->GetPlayerViewPoint(Location, Rotation);
	// DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);
	
	if (MuzzleFlash)
		UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	if (MuzzleSound)
		UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;
	bool bSuccess = GunTrace(HitResult, ShotDirection); 
	if (bSuccess)
	{
		//DrawDebugPoint(GetWorld(), HitResult.Location, 5, FColor::Cyan, true);
		if (BulletImpact)
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),
													 BulletImpact,
													 HitResult.Location,
													 ShotDirection.Rotation());
		if (ImpactSound)
			UGameplayStatics::SpawnSoundAtLocation(GetWorld(),
												   ImpactSound,
												   HitResult.Location);

		AActor* HitActor = HitResult.GetActor();
		
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitActor->GetName());
		if (HitActor)
		{
			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetOwnerController(), this);
		}
	}
}

