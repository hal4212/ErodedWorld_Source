// Fill out your copyright notice in the Description page of Project Settings.
//制作者:21cu0214_榊原暖大
//内容	:敵の親クラス
//最終更新	:2023/06/02

#pragma once

#include "CoreMinimal.h"
#include "ErodedWorldCharacter.h"
#include "GameFramework/Actor.h"
#include "Enemy.generated.h"



//敵のタイプEnum宣言
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

	//変数宣言
	//Enum用変数
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "type")
		EnemyType Type;
	//HP系
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_MaxHP;

	//ノックバック量
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HP")
		float m_Power;

	//フラグ
	//ダメージを受けてるか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDameged;

	//ノックバックするか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isKnockBack;

	//EnemyがHPが０か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDead=false;

	//Bossの死亡確認
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDeathCheck = false;

	//HPが半分を切ったか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isHalf=false;

	//攻撃準備中か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isAtkReady;

	//移動中か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isWalk;


	//チャージエフェクトを出すか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isPreAtk=false;

	//ボスの範囲攻撃ができるか
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isBossRangeAtk;


	//一回目の処理か
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		bool m_isDarty=false;

	//int
	//（わかり次第記入）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "status")
		int m_Cnt;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Damege")
		float m_AddDamage(float _damage);
		virtual float m_AddDamage_Implementation(float _damage);


protected:
	//ダメージ
	

	//HPをチェック
	UFUNCTION(BlueprintCallable, Category = "Check")
		void m_CheckHP();

	//ノックバック
	UFUNCTION(BlueprintCallable, Category = "KnockBack")
		void m_DoKnockBack();

	//ノックバックの力をチェック
	UFUNCTION(BlueprintCallable, Category = "Check")
		float m_CheckPower(float _Vec);

	//プレイヤーの方向を向く処理
	UFUNCTION(BlueprintCallable, Category = "Rotation")
		void m_LookatPlayer();
	
	

protected:
	// Called when the game starts or when spawned
	/*virtual void BeginPlay() override;*/

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
