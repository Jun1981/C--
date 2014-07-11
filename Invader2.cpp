/************************************
*                                  *
*    シューティングゲームループ    *
*                                  *
************************************
*/

//TODO

//init で　全敵の設定


//------ インクルードファイルの読み込み ------//
#include "../../DxLib/DxLib.h"
#include<windows.h>
#include<time.h>
#include <stdlib.h>


//------ 関数のプロトタイプ宣言 ------//
void key_check();           // キー情報取得
void game_main();           // ゲームコントロールメイン
void init();                // ゲームシステム初期化
void haikei();//背景表示

void hyouji_all();//表示全体
void jiki_hyouji();
void jikidan();
void jiki_tenmetsu();
void teki_hyouji();
void tekidan();
void tekidan_idou();
void tekidan_hassha();
void zanki();

void teki_idou();//敵移動関数

void haji_chk();

void counter();//カウンタ関数
void gover_chk();//敵が自分のラインに到達したらゲームオーバー

void teki_atari();
void jiki_atari();


//------ 変数の定義 ------//
int key_trg, Key_Info, Key_Old;   // キー情報
int ChkKAny;                             // とにかくキーが押されたらtrue
int GLpCnt;                             // ゲームループカウンタ

int i, j,k;//ループ用

//キャラ画像のデータ
int title;//タイトル画像読み込み用
int bg; //ゲーム本編背景画像用
int GO;//ゲームオーバー画面読み取り用
int bk;//フェードイン／フェードアウト用
int wt;

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





int rd;//ランダム用変数
int dead_cnt = 100;//死んだときのカウンタ

int haji=0;//敵が端に来たときのフラグ

static int alpha;
int fade_mode=0;//１がフェードイン２がフェードアウト


struct par{

	int x;//x座標
	int y;//y座標
	int sp;//スピード
	int t_sp;//弾スピード
	int dead;//死んでるかどうか

	int life;//残り自機
	int count;//カウンタ

	int haji;//端に行ったかどうかフラグ
	int count_MAX;//カウンタ最大値

	int shot;//弾が出たかどうか

	int kankaku;//敵の弾を撃つ間隔
	int kankaku_sk;//敵の弾うち間隔初期値

	int tama_x;
	int tama_y;


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

	//ランダム生成
	srand((unsigned)time(NULL));

	// ゲーム全体に関わる変数の初期化、画像ファイルの読み込みなどを書く

	LoadDivGraph("../Img/en_my.bmp", 10, 5, 2, 32, 16, chr, 0);//キャラクタ読み込み
	LoadDivGraph("../Img/missile.bmp", 2, 2, 1, 2, 16, tm, 0);//弾画像の読み込み
	title = LoadGraph("../Img/title.bmp");//タイトル画像読み込み
	bg = LoadGraph("../Img/bg.jpg");//ゲーム本編背景画像
	GO = LoadGraph("../Img/gover.jpg");//ゲームオーバー画面
	bk = LoadGraph("../Img/Black.png");//フェード用画面
	wt = LoadGraph("../Img/white.png");//フェード用画面

	FontHandle1 = CreateFontToHandle(NULL, 40, 4);//タイトル用フォントハンドラ;//フォントハンドラ１
	FontHandle2 = CreateFontToHandle(NULL, 16, 8);//ゲーム用フォントハンドラ;//フォントハンドラ２

	migihaji = 450 + 30;//キャラクタ描写領域右端のｘ座標
	hidarihaji = 30;//キャラクタ描写領域左端のｘ座標
	stop = 0;//敵全体をストップする



	lx = 32;//キャラクタ横の長さ
	ly = 16;//キャラクタ縦の長さ

	G_mode = 0;//ゲームモード
	T_Cnt = 20;//タイトル”ＰＵＳＨ　ＳＰＡＣＥ”点滅用カウンタ


	jiki.x = 225 + 32; jiki.y = 480 - (16 * 5), jiki.sp = 2; jiki.t_sp = 4; jiki.dead = 0; jiki.life = 3; jiki.shot = 0;//自機の構造体宣言
	ten.now = 0;//現在スコアの初期化

	//弾関係
	//tama.shot = 0;//弾フラグ０
	//tama.sp = 4;//弾スピード
	
	

	

	
	for (i = 0; i < 11; i++){

		//teki[0][0][i].haji = 0;//敵が端にいるかフラグ

		teki[0][0][i].count_MAX = 50;//敵が何ループごとに動くか
		teki[0][0][i].count = teki[0][0][i].count_MAX;

		teki[0][0][i] .x = (lx - 1) + lx*i;//緑の敵のｘ座標
		teki[0][0][i] .y = ly * 5;//緑の敵の初期ｙ座標
		teki[0][0][i] .kankaku_sk = rand() % 200 + 100;//緑の敵の弾うち間隔

		teki[0][0][i] .kankaku = teki[0][0][i] .kankaku_sk;
		teki[0][0][i] .sp = lx / 2;//敵の一回の移動距離
		teki[0][0][i] .dead = 0;//敵に弾が当たったかどうか（１で当たり）
		
	}
}

/**********************************
*    ゲームコントロールメイン    *
**********************************
*/
void game_main()
{
	//static int alpha;
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
			alpha = 255;
		}

		T_Cnt--;//カウンタを引く
		break;


	case 1://タイトルのフェードアウト
		if (alpha <= 0) {
			G_mode = 10;//ゲーム本編へ
			SetDrawBlendMode( DX_BLENDMODE_NOBLEND , 0 ) ;
			fade_mode = 1;
			break;
		}
		alpha-=4;
		SetDrawBlendMode( DX_BLENDMODE_ALPHA , alpha) ;
		DrawGraph(70, 80, title, TRUE);//タイトルの表示
		break;
	case 10://ゲーム本編
		

		
	
		if (fade_mode == 1){//フェードイン
			if (alpha <= 251){
				alpha += 2;
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			}
		}
		else if (fade_mode == 2){//フェードアウト

			if (alpha <= 0){
				G_mode = 2;//ゲームオーバー
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


			}
			alpha -= 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}
		


		////////////////////////////////////////////////////////////////////////////////////


		
		
		//敵関係

		haji_chk();
		teki_idou();//敵移動関数


		//敵弾発射

		tekidan_hassha();
			//敵弾移動
		   
			tekidan_idou();
			gover_chk();//敵が自分のラインに到達したらゲームオーバー

		
			teki_atari();//自機の弾と敵の当たりチェック
			jiki_atari();//敵弾と自機の当たりチェック
			

			hyouji_all();//表示関数
					
		
	/////////////////////////////////////////////////////////////////
					

		//キー処理/////////////////
		//自機の操作
			if ((Key_Info & 0x01) == 0x01 && jiki.x > 31 && stop == 0 ){
				jiki.x -= jiki.sp;//左へ
				
			}
			if ((Key_Info & 0x02) == 0x02 && jiki.x + lx < 450 + 31 && stop == 0 ){
				jiki.x += jiki.sp;//右へ
				
			}
		if ((key_trg & 0x10) == 0x10 && jiki.shot == 0 && stop == 0)
		{

			tama.x = jiki.x + 15; tama.y = jiki.y;//弾に現在の自機座標代入
			jiki.shot = 1;//弾０の発射
		}
		///////////////////////////////////




		counter();
	

		break;

	case 2://ゲームオーバー
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
			
		}
		DrawGraph(0, 0, GO, TRUE);

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

/////////  表示関係  //////////////////////
void haikei()
{
	DrawGraph(0, 0, bg, TRUE);//背景の表示関数
	DrawFormatStringToHandle(64, 20, GetColor(120, 120, 120), FontHandle2, "Your Score %04d", ten.now);//現在スコアの表示
	DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(120, 120, 120), FontHandle2, "Hi-Score %04d", ten.high);//ハイスコアの表示

}

	//自機関係関数
void hyouji_all(){
	//背景・スコア表示
	haikei();
	zanki();

	////自機の弾表示関係
	if (jiki.shot == 1){
		tama.y -= jiki.t_sp;//弾のｙ座標を引く
		if (tama.y + 16 < 0)
			jiki.shot = 0;

	}

	//自機弾
	if (jiki.shot == 1){
		jikidan();
	}

	//自機の表示
	jiki_hyouji();//自機の表示



	//敵弾表示
	
		tekidan();//敵弾表示
		//敵本体関係
		teki_hyouji();//敵の表示
	}

void jiki_hyouji(){//自機の表示



	if (jiki.dead == 0){
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//自機の表示
		
	}
	else if (jiki.dead == 1){
		
		
		if (dead_cnt % 10 >= 5)
			DrawGraph(jiki.x, jiki.y, chr[5], TRUE);//自機の表示
		else if (dead_cnt % 10<5)
			DrawGraph(jiki.x, jiki.y, chr[6], TRUE);//自機の表示
		if (dead_cnt < 0){
			jiki.dead = 0;
			stop = 0;
			dead_cnt = 100;
		}
	}


}
void jikidan(){//自機の弾表示関数
	DrawGraph(tama.x, tama.y, tm[0], TRUE);//弾０描画
}
void zanki(){//残り自機表示

	for (i = 0; i < jiki.life; i++){
		DrawGraph(480 - lx*(1 + i), 480 - ly, chr[3], TRUE);//自機の表示

	}
}
	

//敵関係関数
void teki_hyouji(){//敵表示
	for (i = 0; i < 11; i++){
		if (teki[0][0][i].dead == 0){
			DrawGraph(teki[0][0][i].x, teki[0][0][i].y, chr[2], TRUE);//敵１の表示
		}
	}
}



//////////////////////////////////////////////////////////////////////////////////

void tekidan_hassha(){
	
	for (i = 0; i < 11; i++){
		teki[0][0][i].kankaku--;
		if (teki[0][0][i].dead == 0)
		{
			if (teki[0][0][i].kankaku<=0 && teki[0][0][i].shot == 0 && stop == 0)
			{
				teki[0][0][i].kankaku = teki[0][0][i].kankaku_sk;
				teki[0][0][i].shot = 1;//玉フラグ１
				teki[0][0][i].tama_x = teki[0][0][i].x + 15;
				teki[0][0][i].tama_y = teki[0][0][i].y;

			}
			
		}
	}
}
void tekidan(){//敵弾表示

	for (i = 0; i < 11; i++){
		if (teki[0][0][i].shot == 1)
			DrawGraph(teki[0][0][i].tama_x, teki[0][0][i].tama_y, tm[1], TRUE);//敵弾の表示
	}
}

//敵弾移動
void tekidan_idou(){
	for (i = 0; i<11; i++){
		if (teki[0][0][i].shot == 1 && stop == 0){
			teki[0][0][i].tama_y += jiki.t_sp;//敵弾のｙ座標を下に
			if (teki[0][0][i].tama_y + 16 >= 640)
				teki[0][0][i].shot = 0;//敵弾フラグ０
		}
	}
}
//////////////////////


/////移動関係関数/////////////////////////
void teki_idou()
{
	if (stop == 0){
		
		if (haji == 0)
		{
			for (i = 0; i < 11; i++){
				teki[0][0][i].count--;
				if (teki[0][0][i].count == 0){
					teki[0][0][i].count = teki[0][0][i].count_MAX;
					teki[0][0][i].x += teki[0][0][i].sp;
				}
			}
		}
		else
		{
			for (i = 0; i < 11; i++){
				teki[0][0][i].count--;
				if (teki[0][0][i].count == 0){
					teki[0][0][i].count = teki[0][0][i].count_MAX;
					teki[0][0][i].y += lx;
					teki[0][0][i].sp = ~teki[0][0][i].sp + 1;
					haji = 0;
				}
			}



			
		}
	}
}
//敵が自分のラインに到達したらゲームオーバー
void gover_chk(){
	for (i = 0; i < 11; i++){
		if (teki[0][0][i].y >= jiki.y){
			stop = 1;
			fade_mode = 2;
			break;
		}
	}
}

void haji_chk(){
	for (i = 0; i < 11; i++){
		if ((teki[0][0][i].x + 32 >= 480 - 1 && teki[0][0][i].sp>0) || (teki[0][0][i].x <= 31 && teki[0][0][i].sp < 0)){
			if (teki[0][0][i].dead == 0){
				haji = 1;
				break;
			}
		}
	}
}


//当たり判定
void teki_atari(){//弾と敵の当たり判定
	for (i = 0; i < 11; i++){
		if (tama.x + 2 >= teki[0][0][i].x + 4 && tama.x <= teki[0][0][i].x + 32 - 4 && tama.y <= teki[0][0][i].y + 16 && tama.y + 16 >= teki[0][0][i].y){
			if (jiki.shot == 1 && teki[0][0][i].dead == 0){
				ten.now += 100;//100点プラス
				jiki.shot = 0;//弾フラグ０
				teki[0][0][i].dead = 1;//敵死亡
			}
		}
	}
}

// 敵弾が自機に当たった時
void jiki_atari(){
	for (i = 0; i<11; i++){
		if (teki[0][0][i].tama_x + 2 > jiki.x && teki[0][0][i].tama_x < jiki.x + 32 && teki[0][0][i].tama_y<jiki.y + 16 && teki[0][0][i].tama_y + 16>jiki.y){
			if (jiki.dead == 0 && teki[0][0][i].shot == 1){

				stop = 1;
				jiki.dead = 1;
				teki[0][0][i].shot = 0;

				teki[0][0][i].kankaku = teki[0][0][i].kankaku_sk;
				jiki.life--;//自機ライフーー
				teki[0][0][i].tama_x = -100;
				teki[0][0][i].tama_y = -100;


				//画面右にHIT表示

				char c[20];
				wsprintf(c, "HIT!");
				DrawString(500, 128, c, GetColor(255, 255, 255));

				if (jiki.life < 0){
					alpha = 255;
					fade_mode = 2;//フェードアウト
					
				}
			}

		}

	}
}


//カウンタ関数

void counter(){
	if (jiki.dead == 0 && stop == 0){
		jiki.count--;
	}

	if (jiki.dead == 1){
		dead_cnt--;
	
	}

}

