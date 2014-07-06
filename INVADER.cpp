/**********************
*                    *
*    ゲームループ    *
*                    *
**********************
*/

#include "../../DxLib/DxLib.h"
#include<windows.h>
#define count_MAX 10



//関数のプロトタイプ宣言
void Shokika();//最初の数値
void Draw_IMG();//画像描写

//変数など

	int i,j;//ループ用

	//キャラ画像のデータ
	int chr[10];//キャラクター分割画像読み込み用変数
	
	int lx=32;//横の長さ
	int ly=16;//縦の長さ
	
	int FontHandle1 = CreateFontToHandle( NULL , 40 , 4 ) ;//タイトル用フォントハンドラ
	int FontHandle2=CreateFontToHandle(NULL,16,8);//ゲーム用フォントハンドラ

	int G_mode=0;//ゲームモード
	int ct=20;//カウンタ
	int title=LoadGraph("../Img/title.bmp");//タイトル画像読み込み
	int bg=LoadGraph("../Img/bg.jpg");//ゲーム本編背景画像
	

	int migihaji=450+30;//右端のｘ座標

	int hidarihaji=30;//左端のｘ座標
	int stop=0;//端に行ったときのストップ
	
	struct par{

		int x;//x座標
		int y;//y座標
		int sp;//スピード
		int hit;//玉が当たったか
		int life;//残り自機
		int count;//カウンタ
		int haji;//端に行ったかどうかフラグ



	};//各キャラのパラメータ

	struct par jiki={225+32,480-(16*5),2,0,3,count_MAX};//自機の構造体宣言
	struct par teki1[11],//敵1(緑１００点）の構造体宣言
		teki2_1[11],teki2_2[11],//敵2(水色5０点）の構造体宣言
	    teki3_1[11],teki3_2[11];//敵3(紫１０点）の構造体宣言
	
	
	struct score{
		int now;//現在スコア
		int high;//ハイスコア
	}ten={0,0};
	



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
	ChangeWindowMode(TRUE);                     // ウインドウモードに変更(ただし、２５６色)

	if(DxLib_Init() == -1) {                    // ＤＸライブラリ初期化処理
		return -1;                             // エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);              // 描画先を裏画面へ
	

/*---------------------
*    Main program    *
*---------------------
*/
	


	

	//------ ゲームループ ------//
	while(CheckHitKey(KEY_INPUT_ESCAPE) == 0) //while-1
	{ // Escキーが押されるまでループ
		ClsDrawScreen();                        // 裏画面クリア

		// ここにゲームの処理プログラムを書く
		Shokika();
		switch(G_mode)
		{

		case 0:


			DrawGraph(70,80,title,TRUE);//タイトルの表示
			SetFontSize(32);// 文字の大きさを指定する

			//スペースキーを押してください画面
			if(ct>10)
			{

				//DrawFormatString(170, 300, GetColor(0, 219, 255), "Push Space Key !"); //文字を画面中央に表示　
				DrawStringToHandle(170, 300,  "Push Space Key !",GetColor(0, 219, 255),FontHandle1); //文字を画面中央に表示　
			}
			else if (ct>0)
			{  
				//DrawFormatString(170, 300, GetColor(0, 0, 0), "Push Space Key !"); //文字を画面中央に表示　
				DrawStringToHandle(170, 300, "Push Space Key !",GetColor(0, 0, 0), FontHandle1); //文字を画面中央に表示
			}
			else if(ct==0)
			{
				ct=20;
			}

			if(CheckHitKey(KEY_INPUT_SPACE))
			{
				G_mode=1;//ゲーム本編へ
				DeleteFontToHandle( FontHandle1 ) ;//フォントハンドラ１を捨てる
				

			}

			ct--;//カウンタを引く
			break;

		case 1://ゲーム本編

			//SetFontSize(20);//フォントの大きさ設定
			//DrawFormatString(80,20,GetColor(100,100,100),"Your Score %d",0);
			
			Draw_IMG();

			if(teki1[0].count==0)
			{
				teki1[0].count=count_MAX;

				if(stop==0)
				{
					teki1[0].x+=teki1[0].sp;//横移動
					if((teki1[0].x+lx>=migihaji && teki1[0].sp>0) ||( teki1[0].x<=0+lx && teki1[0].sp<0) )//端に行ったかどうかチェック
					{
						stop=1;
					}
				}else if(stop==1)

				{
					teki1[0].y+=lx;
					teki1[0].sp=~teki1[0].sp+1;
					stop=0;
				}

				
			}

			teki1[0].count--;



			if(CheckHitKey(KEY_INPUT_RIGHT) && jiki.x<450)
				jiki.x+=jiki.sp;//右へ
			if(CheckHitKey(KEY_INPUT_LEFT) && jiki.x>0+lx)
				jiki.x-=jiki.sp;//左へ



			break;	
		case 2:
			break;
		}

		ScreenFlip();                           // 裏画面を表画面へ
		if(ProcessMessage() == -1) {            // メッセージ処理
			break;                              // エラーが起きたらループから抜ける
		}





	}//while-1

	DxLib_End();                                // ＤＸライブラリ使用の終了処理
	return 0;                                   // ソフトの終了
}

void Shokika(){
	
	for(i=0;i<11;i++)//敵の初期パラメータ
	{

		teki1[i].x=teki2_1[i].x=teki2_2[i].x=teki3_1[i].x=teki3_2[i].x=lx+lx*i;
		teki1[i].y=ly*5;
		teki1[i].sp=teki2_1[i].sp=teki2_2[i].sp=teki3_1[i].sp=teki3_2[i].sp=lx/2;
		teki1[i].hit=teki2_1[i].hit=teki2_2[i].hit=teki3_1[i].hit=teki3_2[i].hit=0;
		teki1[i].count=teki2_1[i].count=teki2_2[i].count=teki3_1[i].count=teki3_2[i].count=count_MAX;
		teki1[i].haji=teki2_1[i].haji=teki2_2[i].haji=teki3_1[i].haji=teki3_2[i].haji=1;

		
		teki2_1[i].y=ly*5+ly;
		teki2_2[i].y=ly*5+ly*2;
		teki3_1[i].y=ly*5+ly*3;
		teki2_2[i].y=ly*5+ly*4;
		

	}
}


void Draw_IMG(){
	
	        DrawGraph(0,0,bg,TRUE);//背景の表示
			DrawFormatStringToHandle(64,20,GetColor(120,120,120),FontHandle2,"Your Score %d",ten.now);//現在スコアの表示
			DrawFormatStringToHandle(450+32-192,20,GetColor(120,120,120),FontHandle2,"Hi-Score %d",ten.high);//ハイスコアの表示
			DrawGraph(jiki.x,jiki.y,chr[3],TRUE);//自機の表示
			DrawGraph(teki1[0].x,teki1[0].y,chr[2],TRUE);//敵１
}