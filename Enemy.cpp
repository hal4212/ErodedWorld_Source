// Fill out your copyright notice in the Description page of Project Settings.
//�����	:21cu0214_�匴�g��
//���e		:�G�̐e�N���X
//�ŏI�X�V	:2023/06/02

#include "Enemy.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"


////////////////////////////////////////////
//AEnemy
AEnemy::AEnemy(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

//��Tick�s������
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//�m�b�N�o�b�N
	if (m_isKnockBack)
	{
		m_CheckPower(DeltaTime);
		m_DoKnockBack();
	}

}

//�_���[�W���󂯂��Ƃ�
float AEnemy::m_AddDamage_Implementation(float _damage)
{
	//�_���[�W�v�Z
	//HP����������𒴂������̕␳���s��
	m_HP = (UKismetMathLibrary::FClamp((int)m_HP + (int)_damage, 0, (int)m_MaxHP));
	m_CheckHP();
	return m_HP;
}

//HP���`�F�b�N
void AEnemy::m_CheckHP()
{
	//HP��0�ȉ��Ȃ�
	if (m_HP <= 0.0)
	{
		//�`���[�W�G�t�F�N�g��؂�
		m_isPreAtk = false;
		//���S�t���O��true��
		m_isDead = true;
	}
	//0�ȏ�ŁA
	else
	{
		//�Ώۂ��{�X�ŁAHP�����߂Ĕ�����؂����Ƃ�
		if (Type==EnemyType::Boss && m_MaxHP / 2 >= m_HP&& !m_isDarty)
		{
			//Half�t���O��true��
			m_isHalf = true;
			//���񂩂𔻒肷��t���O��false��
			m_isDarty = true;
		}
	
	}
}

//�m�b�N�o�b�N
void AEnemy::m_DoKnockBack()
{
	float DeltaLocation = UKismetMathLibrary::Ease(-10.0f, 0.0f, m_Power, EEasingFunc::ExpoOut);
	AddActorLocalOffset(FVector(DeltaLocation,0.f,0.f));
}

//�m�b�N�o�b�N�ʂ����߂�
float AEnemy::m_CheckPower(float _Vec)
{
	if (m_isKnockBack )
	{
		m_Power += _Vec;
	}
	return m_Power;
}


//�v���C���[�̕���������
void AEnemy::m_LookatPlayer()
{
	
	APawn* aPlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	//�����������������v�Z
	FRotator targetRot ;
	//set����
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