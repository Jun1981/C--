/************************************
*                                  *
*    シューティングゲームループ    *
*                                  *
************************************
*/
//------ インクルードファイルの読み込み ------//
#include "../DxLib/DxLib.h"
#include<windows.h>
#include<time.h>
#include <stdlib.h>
#define kazu 300
#define jikidan_kankaku 8 ;

//------ 関数のプロトタイプ宣言 ------//
void start();//タイトル画面
void key_check();           // キー情報取得
void game_main();           // ゲームコントロールメイン
void init();                // ゲームシステム初期化
void haikei();//背景表示
void hyouji_all();//表示全体
void jikidan_hassha();//自機弾発射
void jiki_hyouji();
void jiki_sousa();
void jikidan_hyouji();
void jikidan_idou();
void jiki_tenmetsu();
void teki_hyouji();
void tekidan_hyouji();
void tekidan_idou();
void tekidan_hassha();
void zanki();
void teki_idou();//敵移動関数
void haji_chk();
void counter();//カウンタ関数
void gover_chk();//敵が自分のラインに到達したらゲームオーバー
void teki_atari();//自機弾と敵の当たり判定関数
void jiki_atari();//敵弾と自機の当たり判定関数
void sentou_chk();//敵の列の中で先頭が誰かチェック
void teki_nokori_chk();//敵の残りチェック
void sc_chk();//点数計算
void fade();//フェード関数
//関数宣言終わり

//------ 変数の定義 ------//
int Key_Trg, Key_Info, Key_Old;   // キー情報
int ChkKAny;                             // とにかくキーが押されたらtrue
int GLpCnt;                             // ゲームループカウンタ
int i, j, k,l;//ループ用
int title;//タイトル画像読み込み用
int bg; //ゲーム本編背景画像用
int GO;//ゲームオーバー画面読み取り用
int cl;//クリア画面用
int chr[10];//キャラクター分割画像読み込み用変数
int tm[2];//弾データ読み込み用変数
int FontHandle1;//タイトル用フォントハンドラ;//フォントハンドラ１用
int FontHandle2;//ゲーム用フォントハンドラ;//フォントハンドラ２用
int migihaji;//右端のｘ座標を入れる変数
int hidarihaji;//左端のｘ座標をいれる変数
int T_Cnt;//タイトルのＰＵＳＨ　ＳＰＡＣＥ点滅用

//初期化が必要な変数群
int lx;//キャラクタ横の長さ
int ly;//キャラクタ縦の長さ
int G_mode;//ゲームモード切り替え用
int stop;//端に行った時たてるフラグ
int UFO=0;//UFOフラグ
int dead_cnt;//死んだときのカウンタ
int en_cnt_MAX = 100;//敵が何ループごとに動くか最大値
int en_cnt = en_cnt_MAX;//敵が何ループごとに動くか
int haji ;//敵が端に来たときのフラグ
static signed int alpha;
int fade_mode=0 ;//１がフェードイン２がフェードアウト
int sentou[5][11];
int  teki_nokori ;//敵の残り
int  yoyuu=8;//自機の当たり判定を緩める
struct par{
	int x;//x座標
	int y;//y座標
	int sp;//スピード
	int t_sp;//弾スピード
	int dead;//死んでるかどうか
	int life;//残り自機
	int count;//カウンタ
	int count_MAX;//カウンタ最大値
	int shot[10];//弾が出たかどうか
	int kankaku;//敵の弾を撃つ間隔
	int kankaku_sk;//敵の弾うち間隔初期値
	int tama_x[10];
	int tama_y[10];
	int sentou;//今先頭にいるかどうか
	int flag;//
	int tama_cnt;//自機弾の間隔
};//各キャラのパラメータ
struct score{
	int now;//現在スコア
	int high;//ハイスコア
}ten = { 0, 0 };
struct par teki[3][2][11];///敵の構造体宣言（強さ、何段目か、何列目）	
struct par jiki;//自機の構造体宣言
struct par tama[kazu];//発射した弾

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
		DrawFormatStringToHandle(500, 72, GetColor(255, 255, 255), FontHandle2, "%d", teki_nokori);//敵の残りの数
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
	LoadDivGraph("../Img/en_my.png", 10, 5, 2, 32, 16, chr, 0);//キャラクタ読み込み
	LoadDivGraph("../Img/missile1.png", 2, 2, 1, 2, 16, tm, 0);//弾画像の読み込み
	title = LoadGraph("../Img/title.bmp");//タイトル画像読み込み
	bg = LoadGraph("../Img/bg.jpg");//ゲーム本編背景画像
	GO = LoadGraph("../Img/gover.jpg");//ゲームオーバー画面
	cl = LoadGraph("../Img/gclear.jpg");//クリア画面
	FontHandle1 = CreateFontToHandle(NULL, 40, 4);//タイトル用フォントハンドラ;//フォントハンドラ１
	FontHandle2 = CreateFontToHandle(NULL, 16, 8);//ゲーム用フォントハンドラ;//フォントハンドラ２
	//初期変数数値設定
	lx = 32;//キャラクタ横の長さ
	ly = 16;//キャラクタ縦の長さ
	G_mode = 0;//ゲームモード
	T_Cnt = 20;//タイトル”ＰＵＳＨ　ＳＰＡＣＥ”点滅用カウンタ
	migihaji = 450 + 30;//キャラクタ描写領域右端のｘ座標
	hidarihaji = 30;//キャラクタ描写領域左端のｘ座標
	stop = 0;//敵全体をストップする
	UFO=0;//UFOフラグ０
	dead_cnt=200;//自機死亡カウント初期値
	en_cnt_MAX=100;//敵が何ループごとに動くかの最大値
	en_cnt = en_cnt_MAX;//敵が何ループごとに動くか
	haji = 0;//敵が端に来たときのフラグ
	alpha=0;//フェード用変数
	fade_mode=0;//フェードモード
	teki_nokori=55;//敵の残り
	jiki.x = 225 + 32; jiki.y = 480 - (16 * 5), jiki.sp = 2; jiki.t_sp = 4; jiki.dead = 0; jiki.life = 3; //自機の構造体宣言
	ten.now = 0;//現在スコアの初期化
	jiki.tama_cnt=jikidan_kankaku;
	for (k = 0; k < 11; k++){
		teki[0][0][k].y = ly * 5;//緑の敵の初期ｙ座標
		teki[0][0][k].t_sp = 6;//弾の速さ

		teki[1][0][k].y = ly * 7;//水色１初期ｙ座標
		teki[1][0][k].t_sp = 4;//弾の速さ

		teki[1][1][k].y = ly * 9;//水色２初期ｙ座標
		teki[1][1][k].t_sp = 4;//弾の速さ

		teki[2][0][k].y = ly * 11;//紫１初期ｙ座標
		teki[2][0][k].t_sp = 3;//弾の速さ

		teki[2][1][k].y = ly * 13;//紫２初期ｙ座標
		teki[2][1][k].t_sp = 3;//弾の速さ

		//敵の弾撃ち間隔初期値設定
		for (l = 0; l < 10; l++){
			teki[0][0][k].kankaku_sk = rand() % 30 + 15;//緑の敵の弾うち間隔
			teki[0][0][k].kankaku = teki[0][0][k].kankaku_sk;

			teki[1][0][k].kankaku_sk = rand() % 30 + 60;//水色1敵の弾うち間隔
			teki[1][0][k].kankaku = teki[1][0][k].kankaku_sk;

			teki[1][1][k].kankaku_sk = rand() % 30 + 60;//水色2敵の弾うち間隔
			teki[1][1][k].kankaku = teki[1][1][k].kankaku_sk;

			teki[2][0][k].kankaku_sk = rand() % 50 + 100;//紫１敵の弾うち間隔
			teki[2][0][k].kankaku = teki[2][0][k].kankaku_sk;

			teki[2][1][k].kankaku_sk = rand() % 50 + 100;//紫２敵の弾うち間隔
			teki[2][1][k].kankaku = teki[2][1][k].kankaku_sk;
		}

		//敵関係初期値
		for (j = 0; j < 2; j++){
			for (i = 0; i < 3; i++){
				for (l = 0; l < 10; l++){
					teki[i][j][k].shot[l] = 0;//敵ショットフラグ０
				}
				teki[i][j][k].x = (lx - 1) + lx*k;//緑の敵のｘ座標
				teki[i][j][k].sp = lx / 2;//敵の一回の移動距離
				teki[i][j][k].dead = 0;//敵に弾が当たったかどうか（１で当たり）
				teki[i][j][k].sentou=0;//先頭フラグ
			}
		}
		teki[0][1][k].dead = 1;//余分な敵を殺す(緑の2列目）
	}
	for (i = 0; i < kazu; i++){
		tama[i].flag = 0;//弾が出ていない
	}
}

/**********************************
*    ゲームコントロールメイン    *
**********************************
*/

////メイン//////////////////////////////////////////////////////////////////////

void game_main()
{
	//static int alpha;
	// ゲームの処理を書く
	switch (G_mode)
	{
	case 0:
		start();//スタート画面
		break;
	case 1://タイトルのフェードアウト
		if (alpha <= 0) {
			G_mode = 10;//ゲーム本編へ
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			fade_mode = 1;
			break;
		}
		alpha -= 4;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
 		DrawGraph(70, 80, title, TRUE);//タイトルの表示
		break;
	case 10://ゲーム本編
		
		fade();//フェードイン/アウト
			
		
		if (stop == 0){
			tekidan_hassha();//敵弾発射
			teki_atari();//自機の弾と敵の当たりチェック
			gover_chk();//敵が自分のラインに到達したらゲームオーバー
			jiki_atari();//敵弾と自機の当たりチェック
			jiki_sousa();//自機の移動
			
			teki_idou();//敵移動関数
			haji_chk();
			jikidan_idou();//自機弾移動
			tekidan_idou();//敵弾移動
		}
		
		sentou_chk();//列で誰が先頭にいるか
		teki_nokori_chk();//敵の残りチェック
		hyouji_all();//表示関数
		counter();
		break;
	case 2://ゲームオーバー
		sc_chk();
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}else{
			WaitKey();
			
			if(GetKeyState(0x52)<0){
				init();
				G_mode = 1;//ゲームへ
				break;				
			}
		}
		//DrawGraph(0, 0, GO, TRUE);
	
			SetFontSize(32);// 文字の大きさを指定する
            DrawFormatString(100, 20, GetColor(255, 50, 50), " ゲームオーバー"); 
			DrawFormatString(40, 120, GetColor(255,50,50), "スコア    :%08d点", ten.now); //　現在の点数
			DrawFormatString(40, 190, GetColor(255,50,50), "ハイスコア:%08d点", ten.high); //　ハイスコア
			DrawFormatString(40, 290, GetColor(255,50,50), "もう一度:R"); //　現在の点数
			DrawFormatString(40, 360, GetColor(255,50,50), "やめる  :ESC"); //　ハイスコア
	      
			
		break;
	case 3://クリア
		sc_chk();
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}else {			
			WaitKey();
			if(GetKeyState(0x52)<0){
				init();
				G_mode=1;//ゲームへ
				break;				
			}
		}
		SetFontSize(32);// 文字の大きさを指定する		
			DrawFormatString(100, 20, GetColor(0, 219, 255), "    クリア"); 
			DrawFormatString(40, 90, GetColor(0, 219, 255),  "スコア　  :%08d点", ten.now); //　現在の点数
			DrawFormatString(40, 160, GetColor(0, 219, 255), "ハイスコア:%08d点", ten.high); //　ハイスコア
			
			DrawFormatString(40, 290, GetColor(0,219,255), "もう一度:R"); //　現在の点数
			DrawFormatString(40, 360, GetColor(0,219,255), "やめる  :ESC"); //　ハイスコア
			
		//DrawGraph(0, 0, cl, TRUE);		
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////////

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
	Key_Trg = Key_Info = 0;                                 // キー情報クリア
	ChkKAny = false;
	if (CheckHitKey(KEY_INPUT_LEFT))   { Key_Info |= 0x01; }
	if (CheckHitKey(KEY_INPUT_RIGHT))  { Key_Info |= 0x02; }
	if (CheckHitKey(KEY_INPUT_UP))     { Key_Info |= 0x04; }
	if (CheckHitKey(KEY_INPUT_DOWN))   { Key_Info |= 0x08; }
	if (CheckHitKey(KEY_INPUT_SPACE))  { Key_Info |= 0x10; }
	if (CheckHitKey(KEY_INPUT_Z))      { Key_Info |= 0x20; }
	if (CheckHitKey(KEY_INPUT_ESCAPE)) { Key_Info |= 0x40; }
	if (CheckHitKeyAll()) { ChkKAny = true; }                    // あにー
	Key_Trg = (Key_Info ^ Key_Old) & Key_Info;          // キートリガー情報セット
	Key_Old = Key_Info;                                     // キー情報セーブ
}
/////////  表示関係  //////////////////////
void haikei()
{
	DrawGraph(0, 0, bg, TRUE);//背景の表示関数
	DrawFormatStringToHandle(64, 20, GetColor(255, 255, 255), FontHandle2, "Your Score %04d", ten.now);//現在スコアの表示
	DrawFormatStringToHandle(450 + 32 - 192, 20, GetColor(255, 255, 255), FontHandle2, "Hi-Score %04d", ten.high);//ハイスコアの表示
}
//フェード
void fade(){
	if (fade_mode == 1){//フェードイン
		if (alpha <= 251){
			alpha += 2;
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		}
	}
	else if (fade_mode == 2){//フェードアウト
		if (alpha <= 2){
			G_mode = 2;//ゲームオーバー画面へ
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//break;
		}
		alpha -= 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
	else if (fade_mode == 3){//フェードアウト
		if (alpha <= 2){
			G_mode = 3;//クリア画面へ
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
			//break;
		}
		alpha -= 2;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	}
}
//自機関係関数
void hyouji_all(){
	//背景・スコア表示
	haikei();
	zanki();
	////自機の弾表示関係
	//自機弾
	jikidan_hyouji();
	//敵弾表示
	tekidan_hyouji();//敵弾表示
	jiki_hyouji();//自機の表示
	teki_hyouji();//敵の表示
}
void jiki_hyouji(){//自機の表示
	if (jiki.dead == 0){
		DrawGraph(jiki.x, jiki.y, chr[3], TRUE);//自機の表示
	}
	else if (jiki.dead == 1){
		if (dead_cnt % 10 >= 5)
			DrawGraph(jiki.x, jiki.y, chr[5], TRUE);//自機の表示
		else if (dead_cnt % 10 < 5)
			DrawGraph(jiki.x, jiki.y, chr[6], TRUE);//自機の表示
	}

}
//自機の操作
void jiki_sousa() {
	if ((Key_Info & 0x01)== 0x01 && jiki.x > 31){
		jiki.x -= jiki.sp;//左へ
	}
	if ((Key_Info & 0x02) == 0x02 && jiki.x + lx < 450 + 31){
		jiki.x += jiki.sp;//右へ
	}
	//if (Key_Trg == 0x10){
		if ( (Key_Trg & 0x10) == 0x10 ){
			if(jiki.tama_cnt<=0){
				jiki.tama_cnt=jikidan_kankaku;
		jikidan_hassha();//自機弾発射
			}
	}
}
///////////////////////////////////
void jikidan_hassha(){
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 0 && stop == 0){
			tama[i].x = jiki.x + 15; tama[i].y = jiki.y;//弾に現在の自機座標代入
			tama[i].flag = 1;//弾０の発射
			return;
		}
	}
}
void jikidan_idou(){//自機弾移動
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 1){
			tama[i].y -= jiki.t_sp;//弾のｙ座標を引く
			if (tama[i].y + 16 < 0)//自機弾が上に達したらフラグ０
				tama[i].flag = 0;
		}
	}
}
void jikidan_hyouji(){//自機の弾表示関数
	for (i = 0; i < kazu; i++){
		if (tama[i].flag == 1){
			DrawGraph(tama[i].x, tama[i].y, tm[1], TRUE);//弾０描画
		}
	}
}
void zanki(){//残り自機表示
	for (i = 0; i < jiki.life; i++){
		DrawGraph(480 - lx*(1 + i), 480 - ly, chr[3], TRUE);//自機の表示
	}
}
//敵表示
void teki_hyouji(){//敵表示
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].dead == 0){
					if (UFO == 0){
						if (i == 0){
							DrawGraph(teki[i][0][k].x, teki[i][0][k].y, chr[2], TRUE);//敵１（緑）表示
						}
						else if (i == 1){
							DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[1], TRUE);//敵２（水色）表示
						}
						else if (i == 2){
							DrawGraph(teki[i][j][k].x, teki[i][j][k].y, chr[0], TRUE);//敵3（紫）表示
						}
					}
					else{
						DrawGraph(teki[i][j][k].x, teki[i][j][k].y,chr[4] , TRUE);//UFO表示
					}
				}
			}
		}
	}
}
//敵弾発射
void tekidan_hassha(){
	if (stop == 0){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					teki[i][j][k].kankaku--;
					if (teki[i][j][k].dead == 0 && teki[i][j][k].sentou == 1){
						for (l = 0; l < 10; l++){
							if (teki[i][j][k].kankaku <= 0 && teki[i][j][k].shot[l] == 0 && stop == 0){
								teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
								teki[i][j][k].shot[l] = 1;//玉フラグ１
								teki[i][j][k].tama_x[l] = teki[i][j][k].x + 15;
								teki[i][j][k].tama_y[l] = teki[i][j][k].y;
								return;
							}
						}
					}
				}
			}
		}
	}
}
void tekidan_hyouji(){//敵弾表示
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				for (l = 0; l < 10; l++){
					if (teki[i][j][k].shot[l] == 1)DrawGraph(teki[i][j][k].tama_x[l], teki[i][j][k].tama_y[l], tm[0], TRUE);//敵弾の表示
				}
			}
		}
	}
}
//敵弾移動
void tekidan_idou(){
	
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					for (l = 0; l < 10; l++){
						if (teki[i][j][k].shot[l] == 1){
							teki[i][j][k].tama_y[l] += teki[i][j][k].t_sp;//敵弾のｙ座標を下に
							if (teki[i][j][k].tama_y[l] + 16 >= 640)
								teki[i][j][k].shot[l] = 0;//敵弾フラグ０
						}
					}
				}
			}
		}
	
}
//敵移動
void teki_idou(){
		en_cnt--;
		if (haji == 0){
			if (en_cnt == 0){
				en_cnt = en_cnt_MAX;
				for (i = 0; i < 3; i++){
					for (j = 0; j < 2; j++){
						for (k = 0; k < 11; k++){
							teki[i][j][k].x += teki[i][j][k].sp;
						}
					}
				}
			}
		}
		else{
			if (en_cnt == 0){
				en_cnt = en_cnt_MAX;
				for (i = 0; i < 3; i++){
					for (j = 0; j < 2; j++){
						for (k = 0; k < 11; k++){
							teki[i][j][k].y += lx;
							teki[i][j][k].sp = ~teki[i][j][k].sp + 1;
							haji = 0;
						}
					}
				}
			}
		}
}
//敵が自分のラインに到達したらゲームオーバー
void gover_chk(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if (teki[i][j][k].y >= jiki.y && teki[i][j][k].dead == 0){
					stop = 1;
					fade_mode = 2;
					return;
				}
			}
		}
	}
}
//端に来たかどうか
void haji_chk(){
	for (i = 0; i < 3; i++){
		for (j = 0; j < 2; j++){
			for (k = 0; k < 11; k++){
				if ((teki[i][j][k].x + 32 >= 480 - 1 && teki[i][j][k].sp>0) || (teki[i][j][k].x <= 31 && teki[i][j][k].sp < 0)){
					if (teki[i][j][k].dead == 0){
						haji = 1;
						break;
					}
				}
			}
		}
	}
}
///弾と敵の当たり判定
void teki_atari(){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					for (l = 0; l < kazu; l++){
						if (tama[l].x + 2 >= teki[i][j][k].x + 4 && tama[l].x <= teki[i][j][k].x + 32 - 4 && tama[l].y <= teki[i][j][k].y + 16 && tama[l].y + 16 >= teki[i][j][k].y){
							if (tama[l].flag == 1 && teki[i][j][k].dead == 0){
								tama[l].flag = 0;//弾フラグ０
								teki[i][j][k].dead = 1;//敵死亡
								teki_nokori--;//敵残りの数
								switch (i){
								case 0:
									ten.now += 100;//100点プラス
									break;
								case 1:
									ten.now += 50;//50点プラス
									break;
								case 2:
									ten.now += 10;//10点プラス
									break;
								}
								
							}
						}
					}
				}
			}
		}
	
}
// 敵弾が自機に当たった時
void jiki_atari(){
		for (i = 0; i < 3; i++){
			for (j = 0; j < 2; j++){
				for (k = 0; k < 11; k++){
					for (l = 0; l<10; l++){
						if (teki[i][j][k].tama_x[l] + 2 > jiki.x+yoyuu && teki[i][j][k].tama_x[l] < jiki.x + 32-yoyuu && teki[i][j][k].tama_y[l]<jiki.y + 16 && teki[i][j][k].tama_y[l] + 16>jiki.y){
							if (jiki.dead == 0 && teki[i][j][k].shot[l] == 1 && stop==0){
								stop = 1;
								jiki.dead = 1;
								teki[i][j][k].shot[l] = 0;
								teki[i][j][k].kankaku = teki[i][j][k].kankaku_sk;
								jiki.life--;//自機ライフーー
								teki[i][j][k].tama_x[l] = -100;
								teki[i][j][k].tama_y[l] = -100;								
								if (jiki.life < 0){
									alpha = 255;
									fade_mode = 2;//フェードアウト
									return;
								}
							}
						}
					}
				}
			}
		}	
}
//敵の先頭チェック
void sentou_chk(){
	for (i = 0; i < 11; i++){
		if (teki[2][1][i].dead == 0){
			teki[2][1][i].sentou = 1;
		}
		else if (teki[2][0][i].dead == 0){
			teki[2][1][i].sentou = 0;
			teki[2][0][i].sentou = 1;
		}
		else if (teki[1][1][i].dead == 0){
			teki[2][0][i].sentou = 0;
			teki[1][1][i].sentou = 1;
		}
		else if (teki[1][0][i].dead == 0){
			teki[1][1][i].sentou = 0;
			teki[1][0][i].sentou = 1;
		}
		else if (teki[0][0][i].dead == 0){
			teki[1][0][i].sentou = 0;
			teki[0][0][i].sentou = 1;
		}
		else{
			teki[0][0][i].sentou = 0;
		}
	}
}
//敵の残りに応じた動作
void teki_nokori_chk(){
	if (fade_mode!=3  && fade_mode!=2){
		if (teki_nokori <=5){
			if (UFO == 0){
				en_cnt_MAX = 5;
				UFO = 1;
				for (i = 0; i < 3; i++) {
					for (j = 0; j < 2; j++) {
						for (k = 0; k < 11; k++) {
							teki[i][j][k].t_sp = 6;
							for (l = 0; l < 10; l++) {
								teki[i][j][k].kankaku_sk = rand() % 25;
							}
						}
					}
				}
			}
		}
		if (teki_nokori == 11){
			en_cnt_MAX = 30;
		}
		if (teki_nokori == 22){
			en_cnt_MAX = 50;
		}
		if (teki_nokori == 33){
			en_cnt_MAX = 70;
		}
		if (teki_nokori == 44){
			en_cnt_MAX = 90;
		}
		if (teki_nokori == 0){
			alpha = 255;
			fade_mode = 3;//フェードアウト
		}
	}
}
//スコアチェック
void sc_chk(){
	if (ten.now > ten.high) ten.high = ten.now;
}
//カウンタ関数
void counter(){
	jiki.tama_cnt--;
	if (jiki.dead == 0 && stop == 0){
		jiki.count--;
	}
	if (jiki.dead == 1){
		dead_cnt--;
		if (jiki.life >= 0){
			if (dead_cnt == 100){
				stop = 0;
			}
			else if (dead_cnt == 0){
				dead_cnt = 200;
				jiki.dead = 0;
			}
		}
	}
}
//スタート画面
void start(){
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
}
