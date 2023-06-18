// Fill out your copyright notice in the Description page of Project Settings.
//�����:21cu0214_�匴�g��
//���e	:�G�̐e�N���X
//�ŏI�X�V	:2023/06/02

#pragma once

#include "CoreMinimal.h"
#include "ErodedWorldCharacter.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"



//�G�̃^�C�vEnum�錾
UENUM(BlueprintType, Category = "type")
enum class EnemyType:uint8
{
	Boss,	//0
	Noukin, //1
	Nekura, //2
	Zombie	//3
};

//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "type")
//EnemyType Type;

UCLASS()
class ERODEDWORLD_API AEnemy : public AErodedWorldCharacter
{
	GENERATED_BODY()
	
public:AEnemy(const FObjectInitializer& ObjectInitializer);

	//�ϐ��錾
	//Enum�p�ϐ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "type")
		EnemyType Type;
	//HP�n
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_MaxHP;

	//�m�b�N�o�b�N��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_Power;

	//�t���O
	//�_���[�W���󂯂Ă邩
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDameged;

	//�m�b�N�o�b�N���邩
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isKnockBack;

	//Enemy��HP���O��
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDead=false;

	//Boss�̎��S�m�F
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDeathCheck = false;

	//HP��������؂�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isHalf=false;

	//�U����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isAtkReady;

	//�ړ�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isWalk;


	//�`���[�W�G�t�F�N�g���o����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isPreAtk=false;

	//�{�X�͈͍̔U�����ł��邩
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isBossRangeAtk;


	//���ڂ̏�����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDarty=false;

	//int
	//�i�킩�莟��L���j
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		int m_Cnt;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damege")
		float m_AddDamage(float _damage);
		virtual float m_AddDamage_Implementation(float _damage);


protected:
	//�_���[�W
	

	//HP���`�F�b�N
	UFUNCTION(BlueprintCallable, Category = "Check")
		void m_CheckHP();

	//�m�b�N�o�b�N
	UFUNCTION(BlueprintCallable, Category = "KnockBack")
		void m_DoKnockBack();

	//�m�b�N�o�b�N�̗͂��`�F�b�N
	UFUNCTION(BlueprintCallable, Category = "Check")
		float m_CheckPower(float _Vec);

	//�v���C���[�̕�������������
	UFUNCTION(BlueprintCallable, Category = "Rotation")
		void m_LookatPlayer();
	
	

protected:
	// Called when the game starts or when spawned
	/*virtual void BeginPlay() override;*/

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
