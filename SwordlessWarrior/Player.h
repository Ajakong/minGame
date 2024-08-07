#pragma once
#include"Object.h"



class Player : public Object
{
public:
	Player(int modelhandle);
	~Player();

	void Init();

	void Update();
	void Draw();

	
	void SetCameraToPlayer(VECTOR cameraToPlayer);
	
	void Hit();
	int WatchHp()const { return m_Hp; }

	void SetCameraAngle(float cameraAngle);

	int GetPlayerModelhandle() { return m_modelHandle; }

	//メンバ関数ポインタ
	using playerState_t = void(Player::*)();
	playerState_t m_playerUpdate;

private:
	//アニメーションの進行
	//ループしたかどうかを返す
	bool UpdateAnim(int attachNo);
	//アニメーションの変更
	void ChangeAnim(int animIndex);

	//状態別関数(ポインタで呼び出す)
	
	/// <summary>
	/// 開始直後に呼ばれる
	/// </summary>
	void StartUpdate();
	/// <summary>
	/// 通常時
	/// </summary>
	void NeutralUpdate();
	void WalkingUpdate();
	void JumpingUpdate();
	/// <summary>
	/// 衝突関数
	/// </summary>
	void HitUpdate();
	/// <summary>
	/// 回避
	/// </summary>
	void AvoidUpdate();

	VECTOR GetCameraToPlayer()const;

private:
	int m_Hp;
	int m_modelHandle = 0;

	int rotRad = 0;

	/// <summary>
	/// 行動のフレームを管理する
	/// </summary>
	int actionFrame = 0;

	float m_radius = 0;

	VECTOR m_velocity;
	VECTOR m_cameraToPlayer;

	int m_currentAnimNo;//現在のアニメーション
	int m_prevAnimNo;//変更前のアニメーション
	float m_animBlendRate;//アニメーションの合成割合
	//0.0f:prevが再生
	//1.0:currentが再生

	//アニメーション変数
	int m_anim_nutral = 0;
	int m_anim_move = 0;
	int m_anim_hit = 0;
	int m_anim_jump = 0;
	int m_attach_move = 0;
	int m_attach_hit = 0;
	int m_attach_jump = 0;
	int m_attach_nutral = 0;

	float m_playAnimTime = 0.0f;
	float m_animTime_move = 0.0f;
	
	float m_playerRotateY = 0;
	float m_cameraAngle = 0;

	bool m_isVisibleFlag = false;
	int m_visibleCount = 0;

	int HitCount = 0;
};

