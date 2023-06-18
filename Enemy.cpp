// Fill out your copyright notice in the Description page of Project Settings.
//制作者	:21cu0214_榊原暖大
//内容		:敵の親クラス
//最終更新	:2023/06/02

#include "Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


////////////////////////////////////////////
//AEnemy
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

//毎Tick行う処理
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//ノックバック
	if (m_isKnockBack)
	{
		m_CheckPower(DeltaTime);
		m_DoKnockBack();
	}

}

//ダメージを受けたとき
float AEnemy::m_AddDamage_Implementation(float _damage)
{
	//ダメージ計算
	//HPが上限下限を超えた時の補正も行う
	m_HP = (UKismetMathLibrary::FClamp((int)m_HP + (int)_damage, 0, (int)m_MaxHP));
	m_CheckHP();
	return m_HP;
}

//HPをチェック
void AEnemy::m_CheckHP()
{
	//HPが0以下なら
	if (m_HP <= 0.0)
	{
		//チャージエフェクトを切る
		m_isPreAtk = false;
		//死亡フラグをtrueに
		m_isDead = true;
	}
	//0以上で、
	else
	{
		//対象がボスで、HPが初めて半分を切ったとき
		if (Type==EnemyType::Boss && m_MaxHP / 2 >= m_HP&& !m_isDarty)
		{
			//Halfフラグをtrueに
			m_isHalf = true;
			//初回かを判定するフラグをfalseに
			m_isDarty = true;
		}
	
	}
}

//ノックバック
void AEnemy::m_DoKnockBack()
{
	float DeltaLocation = UKismetMathLibrary::Ease(-10.0f, 0.0f, m_Power, EEasingFunc::ExpoOut);
	AddActorLocalOffset(FVector(DeltaLocation,0.f,0.f));
}

//ノックバック量を決める
float AEnemy::m_CheckPower(float _Vec)
{
	if (m_isKnockBack )
	{
		m_Power += _Vec;
	}
	return m_Power;
}


//プレイヤーの方向を向く
void AEnemy::m_LookatPlayer()
{
	
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	//向かせたい方向を計算
	FRotator targetRot ;
	//setする
	if (m_isWalk )
	{
		targetRot = UKismetMathLibrary::RInterpTo(GetActorRotation(), FRotator(0.f, targetRot.Yaw, 0.f), UGameplayStatics::GetWorldDeltaSeconds(GetWorld()), 0.f);
	}
	else
	{
		targetRot = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), aPlayerPawn->GetActorLocation());
		SetActorRotation(FRotator(0.f, targetRot.Yaw, 0.f));
		m_isKnockBack = true;

		
	}
	SetActorRotation(FRotator(0.f, targetRot.Yaw, 0.f));
}