/************************************
*                                  *
*    シューティングゲームループ    *
*                                  *
************************************
*/

//------ インクルードファイルの読み込み ------//
#include "../../DxLib/DxLib.h"
#include<windows.h>


//------ 関数のプロトタイプ宣言 ------//
void key_check();           // キー情報取得
void game_main();           // ゲームコントロールメイン
void init();                // ゲームシステム初期化

//------ 変数の定義 ------//
int key_trg, Key_Info, Key_Old;   // キー情報
int ChkKAny;                             // とにかくキーが押されたらtrue
int GLpCnt;                             // ゲームループカウンタ

int i, j;//ループ用

//キャラ画像のデータ
int chr[10];//キャラクター分割画像読み込み用変数
int tm[2];//弾データ読み込み用変数

int lx;//キャラクタ横の長さ
int ly;//キャラクタ縦の長さ


int G_mode;//ゲームモード切り替え用
int T_Cnt;//タイトルのＰＵＳＨ　ＳＰＡＣＥ点滅用

int migihaji;//右端のｘ座標を入れる変数

int hidarihaji;//左端のｘ座標をいれる変数
int stop;//端に行った時たてるフラグ


int FontHandle1;//タイトル用フォントハンドラ;//フォントハンドラ１用
int FontHandle2;//ゲーム用フォントハンドラ;//フォントハンドラ２用


int title;//タイトル画像読み込み用
int bg; //ゲーム本編背景画像用



struct par{

	int x;//x座標
	int y;//y座標
	int sp;//スピード
	int dead;//死んでるかどうか

	int life;//残り自機
	int count;//カウンタ

	int haji;//端に行ったかどうかフラグ
	int count_MAX;//カウンタ最大値

	int shot;//弾が出たかどうか


};//各キャラのパラメータ


struct par teki[3][2][11];///敵の構造体宣言（強さ、何段目か、何列目）	

struct score{
	int now;//現在スコア
	int high;//ハイスコア
}ten = { 0, 0 };

struct par jiki;//自機の構造体宣言
struct par tama;//発射した弾




/**********************
*    Main program    *
**********************
*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);                     // ウインドウモードに変更(ただし、２５６色)

	if (DxLib_Init() == -1) {                    // ＤＸライブラリ初期化処理
		return -1;                              // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);              // 描画先を裏画面へ

	init();                                     // ゲームシステム初期化

	//------ ゲームループ ------//
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) { // Escキーが押されるまでループ
		ClsDrawScreen();                        // 裏画面クリア

		key_check();                            // キー情報取得
		game_main();                            // ゲームコントロールメイン
		GLpCnt++;                               // ゲームループカウンタをプラス

		/////////////////// For debug
		// フレーム（ゲーム）カウント表示
		char b[20];
		wsprintf(b, "%08X", GLpCnt);
		DrawString(500, 32, b, GetColor(255, 255, 255));
		wsprintf(b, "%08X", Key_Info);
		DrawString(500, 52, b, GetColor(255, 255, 255));
		/////////////////// For debug

		ScreenFlip();                           // 裏画面を表画面へ
		if (ProcessMessage() == -1) {            // メッセージ処理
			break;                              // エラーが起きたらループから抜ける
		}
	}
	DxLib_End();                                // ＤＸライブラリ使用の終了処理
	return 0;                                   // アプリケーションの終了
}


/*-----------------------------
*    ゲームシステム初期化    *
*-----------------------------
*/
void init()
{
	// ゲーム全体に関わる変数の初期化、画像ファイルの読み込みなどを書く

	LoadDivGraph("../Img/en_my.bmp", 10, 5, 2, 32, 16, chr, 0);//キャラクタ読み込み
	LoadDivGraph("../Img/missile.bmp", 2, 2, 1, 2, 16, tm, 0);//弾画像の読み込み
	title = LoadGraph("../Img/title.bmp");//タイトル画像読み込み
	bg = LoadGraph("../Img/bg.jpg");//ゲーム本編背景画像

	FontHandle1 = CreateFontToHandle(NULL, 40, 4);//タイトル用フォントハンドラ;//フォントハンドラ１
	FontHandle2 = CreateFontToHandle(NULL, 16, 8);//ゲーム用フォントハンドラ;//フォントハンドラ２

	migihaji = 450 + 30;//キャラクタ描写領域右端のｘ座標
	hidarihaji = 30;//キャラクタ描写領域左端のｘ座標
	stop = 0;//敵全体をストップする

	lx = 32;//キャラクタ横の長さ
	ly = 16;//キャラクタ縦の長さ

	G_mode = 0;//ゲームモード
	T_Cnt = 20;//タイトル”ＰＵＳＨ　ＳＰＡＣＥ”点滅用カウンタ

	jiki = { 225 + 32, 480 - (16 * 5), 2, 0, { 0 /*tama*/ }, 3, 20 };//自機の構造体宣言
	ten.now = 0;//現在スコアの初期化

	//弾関係
	tama.shot = 0;//弾フラグ０
	tama.sp = 4;//弾スピード

	for (i = 0; i < 11; i++)//敵の初期パラメータ
	{
		//敵１（緑の一番上のヤツ　100点）
		//teki1[i].x = teki2_1[i].x = teki2_2[i].x = teki3_1[i].x = teki3_2[i].x = (lx - 1) + lx*i;//敵のｘ座標
		
		teki[0][0][i].x = (lx - 1) + lx*i;//緑の敵のｘ座標



		teki[0][0][i].y = ly * 5;//緑の敵の初期ｙ座標
		teki[1][0][i].y = ly * 5 + ly;//水色の敵１
		teki[1][1][i].y = ly * 5 + ly*2;//水色の敵２
		teki[2][0][i].y = ly * 5 + ly * 3;//紫の敵１
		teki[2][1][i].y = ly * 5 + ly * 4;//紫の敵2



		//teki1[i].y = ly * 5;//敵のｙ座標初期化

		teki[0][0][i].sp = lx / 2;//敵の一回の移動距離
		//teki1[i].sp = teki2_1[i].sp = teki2_2[i].sp = teki3_1[i].sp = teki3_2[i].sp = lx / 2;//敵の一回での移動距離

		//teki1[i].dead = teki2_1[i].dead = teki2_2[i].dead = teki3_1[i].dead = teki3_2[i].dead = 0;//敵に弾が当たったかどうか（１で当たり）
		teki[0][0][i].dead  = 0;//敵に弾が当たったかどうか（１で当たり）

		//teki1[i].count_MAX = 40;//敵スピードカウンタの最大値
	    teki[0][0][i].count_MAX = 40;//敵スピードカウンタの最大値

		//teki1[i].count = teki2_1[i].count = teki2_2[i].count = teki3_1[i].count = teki3_2[i].count = teki1[i].count_MAX;//何フレームおきに移動するか
		teki[0][0][i].count = teki[0][0][i].count_MAX;//

		//teki1[i].haji = teki2_1[i].haji = teki2_2[i].haji = teki3_1[i].haji = teki3_2[i].haji = 3;//敵が端に着いたかどうか（１で着いた）
		teki[0][0][i].haji = 3;//敵が端に着いたかどうか（１で着いた）


	

	}

}


/**********************************
*    ゲームコントロールメイン    *
**********************************
*/
void game_main()
{
	// ゲームの処理を書く
	switch (G_mode)
	{

	case 0:


		DrawGraph(70, 80, title, TRUE);//タイトルの表示


		//スペースキーを押してください画面
		if (T_Cnt > 10)
		{

			DrawStringToHandle(170, 300, "Push Space Key !", GetColor(0, 219, 255), FontHandle1); //文字を画面中央に表示　
		}
		else if (T_Cnt > 0)
		{

			DrawStringToHandle(170, 300, "Push Space Key !", GetColor(0, 0, 0), FontHandle1); //文字を画面中央に表示
		}
		else if (T_Cnt == 0)
		{
			T_Cnt = 20;
		}

		if (CheckHitKey(KEY_INPUT_SPACE))
		{
			G_mode = 1;//ゲーム本編へ
			DeleteFontToHandle(FontHandle1);//フォントハンドラ１を捨てる

		}

		T_Cnt--;//カウンタを引く
		break;

	case 1://ゲーム本編

		//SetFontSize(20);//フォントの大きさ設定
		//DrawFormatString(80,20,GetColor(100,100,100),"Your Score %d",0);

		DrawGraph(0, 0, bg, TRUE);//背景の表示
		DrawFormatStringToHandle(64, 20, GetColor(120, 120, 120), FontHandle2, "Your Score %04d", ten.now);//現在スコアの表示
		DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(120, 120, 120), FontHandle2, "Hi-Score %04d", ten.high);//ハイスコアの表示


		//弾と敵の当たり判定
		if (tama.shot == 1 && teki[0][0][0].dead == 0 && tama.x + 2 >= teki[0][0][0].x+4 && tama.x <= teki[0][0][0].x + 32-4 && tama.y <= teki[0][0][0].y + 16 && tama.y + 16 >= teki[0][0][0].y)
		{
			ten.now += 100;//100点プラス
			tama.shot = 0;//弾フラグ０
			teki[0][0][0].dead = 1;//敵死亡
		}
		//敵の処理
		if (teki[0][0][0].count == 0)
		{
			teki[0][0][0].count = 40;

			if (stop == 0)
			{
				teki[0][0][0].x += teki[0][0][0].sp;//横移動
				if ((teki[0][0][0].x + lx + 1 >= migihaji && teki[0][0][0].sp > 0) || (teki[0][0][0].x - 1 <= 30 && teki[0][0][0].sp < 0))//端に行ったかどうかチェック
				{
					stop = 1;
				}
			}
			else if (stop == 1)

			{
				teki[0][0][0].y += lx;
				teki[0][0][0].sp = ~teki[0][0][0].sp + 1;
				stop = 0;
			}
						


		}


		
		if (tama.shot == 1){
			DrawGraph(tama.x, tama.y, tm[0], TRUE);//弾０描画
			tama.y -= tama.sp;//弾のｙ座標を引く
		}
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//自機の表示
		if (teki[0][0][0].dead == 0)
		{

			DrawGraph(teki[0][0][0].x, teki[0][0][0].y, chr[2], TRUE);//敵１
		}

		
	

		

		teki[0][0][0].count--;



		//if (CheckHitKey(KEY_INPUT_RIGHT) && jiki.x<450)
		//	jiki.x += jiki.sp;//右へ
		//if (CheckHitKey(KEY_INPUT_LEFT) && jiki.x>0 + lx)
		//	jiki.x -= jiki.sp;//左へ

		//時機の操作
		if ((Key_Info&0x01) == 0x01 && jiki.x > 31)
			jiki.x -= jiki.sp;//左へ
		if ((Key_Info&0x02) == 0x02 && jiki.x + lx < 450 + 31)
			jiki.x += jiki.sp;//右へ
		if ((key_trg&0x10) == 0x10 && tama.shot == 0)
		{

			tama.x = jiki.x+15; tama.y = jiki.y;//弾に現在の自機座標代入
			tama.shot = 1;//弾０の発射
		}
		if (tama.y < 0)
		{

			tama.shot = 0;//弾フラグ０
		}

		break;

	case 2:
		break;
	}
}



/*---------------------
*    キー情報取得    *
*---------------------
*
*    LEFT  = 0000 0001
*    RIGHT = 0000 0010
*    UP    = 0000 0100
*    DOWN  = 0000 1000
*    key_trgは押した瞬間の情報
*    key_infoは今の状態
*
*/
void key_check()
{
	key_trg = Key_Info = 0;                                 // キー情報クリア
	ChkKAny = false;

	if (CheckHitKey(KEY_INPUT_LEFT))   { Key_Info |= 0x01; }
	if (CheckHitKey(KEY_INPUT_RIGHT))  { Key_Info |= 0x02; }
	if (CheckHitKey(KEY_INPUT_UP))     { Key_Info |= 0x04; }
	if (CheckHitKey(KEY_INPUT_DOWN))   { Key_Info |= 0x08; }

	if (CheckHitKey(KEY_INPUT_SPACE))  { Key_Info |= 0x10; }
	if (CheckHitKey(KEY_INPUT_Z))      { Key_Info |= 0x20; }
	if (CheckHitKey(KEY_INPUT_ESCAPE)) { Key_Info |= 0x40; }
	if (CheckHitKeyAll()) { ChkKAny = true; }                    // あにー
	key_trg = (Key_Info ^ Key_Old) & Key_Info;          // キートリガー情報セット
	Key_Old = Key_Info;                                     // キー情報セーブ
}

