#pragma once

/// <summary>
/// 衝突管理クラス
/// </summary>
class CollisionMaster
{
public:
	CollisionMaster();
	~CollisionMaster();

	void Entry();//衝突したオブジェクトを取得
	void Judge();//関係性を判別
	void Exit();//削除
};

