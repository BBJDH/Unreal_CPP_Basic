

#include "03_Collision/C06_Explosion.h"
#include "Global.h"
#include "C06_EventTrigger.h"
#include "Particles/ParticleSystem.h"
#include "Components/TextRenderComponent.h"
AC06_Explosion::AC06_Explosion()
{
	CHelpers::CreateComponent<USceneComponent>(this, &Root, "Root");

	CreateTextRender();

	//파티클 할당
	CHelpers::GetAsset<UParticleSystem>(&Particles[0], "ParticleSystem'/Game/M5VFXVOL2/Particles/Explosion/Fire_Exp_00.Fire_Exp_00'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[1], "ParticleSystem'/Game/M5VFXVOL2/Particles/Explosion/Fire_Exp_01.Fire_Exp_01'");
	CHelpers::GetAsset<UParticleSystem>(&Particles[2], "ParticleSystem'/Game/M5VFXVOL2/Particles/Explosion/Fire_Exp_03.Fire_Exp_03'");
}

void AC06_Explosion::BeginPlay()
{
	Super::BeginPlay();
	
	AC06_EventTrigger* trigger = CHelpers::FindActor<AC06_EventTrigger>(GetWorld());
	CheckNull(trigger);

	trigger->OnExplosionEvent.AddUFunction(this, "OnExplosion");


}


void AC06_Explosion::OnExplosion(int32 InIndex)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Particles[InIndex], GetActorLocation());
}