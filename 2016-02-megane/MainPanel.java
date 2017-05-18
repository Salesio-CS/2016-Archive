import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Random;

import javax.sound.midi.InvalidMidiDataException;
import javax.sound.midi.MidiUnavailableException;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;
import javax.swing.JPanel;

/*
 * Created on 2005/02/09
 *
 */

/**
 * メインパネル
 *
 * @author mori
 *
 */
public class MainPanel extends JPanel implements Runnable, KeyListener {
    // パネルサイズ
    public static final int WIDTH = 1792 ;
    public static final int HEIGHT = 1008 ;

    // 方向定数
    private static final int LEFT = 1;
    private static final int RIGHT = 1;

    // 連続発射できる弾の数
    private static final int NUM_SHOT = 100;
    // 発射できる間隔（弾の充填時間）
    private static final int FIRE_INTERVAL = 30;

    // エイリアンの数
    private static final int NUM_ALIEN = 1;
    //
    private static final int NUM_BOSS = 10;

    Mob_enemy[] mob_enemy;
    private static final int NUM_MOB_ENEMY = 30;

    public static int[] logtime =
    	{400, 450, 500, 800, 850,
    	900, 1200, 1250, 1300, 1600,
    	1650, 1700, 2000, 2050, 2100,
    	2400, 2450, 2500, 2800, 2850, 2900};

    //int Alien Alien.boss_flag;

    // 砲台の数
    // ビームの数
    // ボス初期HP
    private final int farstHP = 500;

    // プレイヤー
    public Player player;
    // 弾
    private Shot[] shots;
    // 最後に発射した時間
    private long lastFire = 0;
    // エイリアン
    Alien[] aliens;
    // 砲台
    private enemy_bullet[] enemy_bullet;
    private static final int NUM_ALIEN_bullet = 108;
    // ビーム
    private Beam[] beams;
    private static final int NUM_BEAM = 250;
    private static final int BOS_BEAM = 100;
    // 自機狙い
    private Lockon lockon;

    int time=0;

    private HPLayer hpbar;
    private int asleep = 0;

    //背景描写に使用
    private Back back;
    public int time_e = 0;
    public int count = 0;
    public int BACK_WIDTH = 0;
    public static int frag_title=0;//条件関数

    // 爆発エフェクト
    private Explosion explosion;
    // ウサタンクのHP
    private int HP=farstHP;

    // キーの状態（このキー状態を使ってプレイヤーを移動する）

    private boolean upPressed 		= false;
    private boolean downPressed 	= false;
    private boolean rightPressed	= false;
    private boolean leftPressed		= false;


    public double x_vect = 0;
    public double y_vect = 0;

    private boolean firePressed 	= false;
    private boolean goodgame 		= false;

    // ゲームループ用スレッド
    private Thread gameLoop;

    // 乱数発生器
    private Random rand;

    // サウンド
    private static String[] soundNames = {"bom28_a.wav", "puu38.wav", "puu51.wav"};

    public MainPanel() {
        // パネルの推奨サイズを設定、pack()するときに必要
        setPreferredSize(new Dimension(WIDTH, HEIGHT));
        // パネルがキー入力を受け付けるようにする
        setFocusable(true);

        // ゲームの初期化
        initGame();

        rand = new Random();

        // サウンドをロード
        for (int i=0; i<soundNames.length; i++) {
            try {
                WaveEngine.load("se/" + soundNames[i]);
            } catch (LineUnavailableException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            } catch (UnsupportedAudioFileException e) {
                e.printStackTrace();
            }
        }

        // BGMをロード
        try {
            MidiEngine.load("bgm/tam-g07.mid");
        } catch (MidiUnavailableException e) {
            e.printStackTrace();
        } catch (InvalidMidiDataException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // BGMを再生
        MidiEngine.play(0);


      //タイトル描画
    	back = new Back(WIDTH,HEIGHT,this);
        BACK_WIDTH = back.backwidth();

        InputStreamReader jinbi = new InputStreamReader(System.in);       //（１）
        BufferedReader nyuryoku = new BufferedReader(jinbi);                    //（２）


        // キーイベントリスナーを登録
        addKeyListener(this);

        //タイトル

        // ゲームループ開始
        gameLoop = new Thread(this);
        gameLoop.start();
    }

    /**
     * ゲームループ
     */
    public void run() {
        while (true) {
        	//タイトル表示
        	if(firePressed == true&&MainPanel.frag_title == 0){
	        	MainPanel.frag_title =1;

	        	back = new Back(WIDTH,HEIGHT,this);
	            BACK_WIDTH = back.backwidth();

	            InputStreamReader jinbi = new InputStreamReader(System.in);       //（１）
	            BufferedReader nyuryoku = new BufferedReader(jinbi);                    //（２）
	        	}

            while(MainPanel.frag_title == 1){

            //移動コマンド
        	move();
            // 発射ボタンが押されたら弾を発射
            if (firePressed) {tryToFire();}

            // エイリアンの攻撃
            alienAttack();

            // 衝突判定
            collisionDetection();

            WaveEngine.render();


            // 再描画
            repaint();

            // 休止
            try {
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            }
        }
    }

    /**
     * ゲームの初期化
     */
    private void initGame() {
        // プレイヤーを作成
        player = new Player(0,HEIGHT / 2, this);

        //player = new Player(WIDTH / 2,HEIGHT / 2, this);//Debug


        //背景を作成
        //back = new Back(WIDTH,HEIGHT,this);
        //BACK_WIDTH = back.backwidth();

        // 弾を作成
        shots = new Shot[NUM_SHOT];
        for (int i = 0; i < NUM_SHOT; i++) {
            shots[i] = new Shot(this);
        }

        // エイリアンを作成
        aliens = new Alien[NUM_ALIEN];
        for (int i = 0; i < NUM_ALIEN; i++) {
            aliens[i] = new Alien(20 + (i % 10) * 40, 20 + (i / 10) * 40, 1, this);
        }
        // エイリアンの砲台を作成
        enemy_bullet = new enemy_bullet[NUM_ALIEN_bullet];
        for (int i = 0; i < NUM_ALIEN_bullet; i++) {
            enemy_bullet[i] = new enemy_bullet( (i % 8) * 80,  (i / 8) * 80, 12, this);
        }

        mob_enemy = new Mob_enemy[NUM_MOB_ENEMY];//雑魚作成
        for (int i = 0; i < NUM_MOB_ENEMY; i++) {
            mob_enemy[i] = new Mob_enemy(this);
        }

        // ビームを作成
        beams = new Beam[NUM_BEAM];
        for (int i = 0; i < NUM_BEAM; i++) {
            beams[i] = new Beam(this);
        }
        // 自機狙いシステム作成
        lockon = new Lockon(this,player.x,player.y);

        //HPバー作成
        hpbar = new HPLayer(this);

        //定数代入
        count = 0;
        time_e = 0;
        HP = farstHP;
    }

    /**
     * 移動処理
     */
    private void move() {

        // プレイヤーを移動する
        // 何も押されていないときは移動しない
    	x_vect = flgchanger(upPressed,downPressed);
    	y_vect = flgchanger(rightPressed,leftPressed);

    	player.move(x_vect,y_vect);

        // エイリアンを移動する(固定済み)

        // 砲台を移動する(固定済み)
        for (int i = 0; i < NUM_ALIEN_bullet; i++) {
            enemy_bullet[i].move();
        }
        //雑魚を移動する
        
        	time_e++;
        	 for (int i = 0; i < NUM_ALIEN; i++) {
                 aliens[i].move();
             }
        	
        		if(time_e >= logtime[20]){
        			mob_enemy[24].moveflg[1] = true;
        			mob_enemy[27].moveflg[2] = true;
        		}if(time_e >= logtime[19]){
        				mob_enemy[25].moveflg[1] = true;
        				mob_enemy[28].moveflg[2] = true;
        		}if(time_e >= logtime[18]){
                    	mob_enemy[26].moveflg[1] = true;
                    	mob_enemy[29].moveflg[2] = true;
        		}if(time_e >= logtime[17]){
                    	mob_enemy[18].moveflg[0] = true;
                    	mob_enemy[21].moveflg[2] = true;
            	}if(time_e >= logtime[16]){
                    	mob_enemy[19].moveflg[0] = true;
                    	mob_enemy[22].moveflg[2] = true;
            	}if(time_e >= logtime[15]){
                    	mob_enemy[20].moveflg[0] = true;
                    	mob_enemy[23].moveflg[2] = true;
            	}if(time_e >= logtime[14]){
                    	mob_enemy[12].moveflg[1] = true;
                    	mob_enemy[15].moveflg[0] = true;
            	}if(time_e >= logtime[13]){
                    	mob_enemy[13].moveflg[1] = true;
                    	mob_enemy[16].moveflg[0] = true;
            	}if(time_e >= logtime[12]){
                    	mob_enemy[14].moveflg[1] = true;
                    	mob_enemy[17].moveflg[0] = true;
        		}if(time_e > logtime[11]){
                		mob_enemy[9].moveflg[2] = true;
            	}if(time_e > logtime[10]){
                    	mob_enemy[10].moveflg[2] = true;
            	}if(time_e > logtime[9]){
                    	mob_enemy[11].moveflg[2] = true;
            	}if(time_e > logtime[8]){
                    	mob_enemy[6].moveflg[0] = true;
            	}if(time_e > logtime[7]){
                    	mob_enemy[7].moveflg[0] = true;
            	}if(time_e > logtime[6]){
                    	mob_enemy[8].moveflg[0] = true;
            	}if(time_e > logtime[5]){
                    	mob_enemy[3].moveflg[0] = true;
            	}if(time_e > logtime[4]){
            			mob_enemy[4].moveflg[0] = true;
            	}if(time_e > logtime[3]){
                		mob_enemy[5].moveflg[0] = true;
        		}if(time_e > logtime[2]){
                    	mob_enemy[2].moveflg[1] = true;
        		}if(time_e > logtime[1]){
                    	mob_enemy[1].moveflg[1] = true;
            	}if(time_e > logtime[0]){
                    	mob_enemy[0].moveflg[1] = true;
            	}
            	for (int i = 0; i < NUM_MOB_ENEMY; i++) {
            		mob_enemy[i].move();
        	}
        
        // 弾を移動する
        for (int i = 0; i < NUM_SHOT; i++) {
            shots[i].move();
        }

        lockon.update(player.x,player.y);

        // ビームを移動する
        for (int i = 0; i < NUM_BEAM; i++) {
            beams[i].move();
        }

        count++;

    }

    /**
     * 弾を発射する
     */
    private void tryToFire() {
        // 前との発射間隔がFIRE_INTERVAL以下だったら発射できない
        if (System.currentTimeMillis() - lastFire < FIRE_INTERVAL) {
            return;
        }

        lastFire = System.currentTimeMillis();
        // 発射されていない弾を見つける
        for (int i = 0; i < NUM_SHOT; i++) {
            if (shots[i].isInStorage()) {
                // 弾が保管庫にあれば発射できる
                // 弾の座標をプレイヤーの座標にすれば発射される
                Point pos = player.getPos();
                shots[i].setPos(pos.x + player.getWidth() / 2, pos.y);
                // 発射音
                WaveEngine.play(2);
                // 1つ見つけたら発射してbreakでループをぬける
                break;
            }
        }
    }

    /**
     * エイリアンの攻撃
     */
    private void alienAttack() {

    	if(aliens[0].boss_flag==1){
    		//ボス砲撃
    		// 1ターンでNUM_BEAMだけ発射する
    		// つまりエイリアン1人になってもそいつがNUM_BEAM発射する
    		//for (int i = 0; i < NUM_BEAM/2; i++) {
    		for (int i = 0; i < BOS_BEAM / 2; i++) {
    			// エイリアンの攻撃
    			// ランダムにエイリアンを選ぶ
    			int n1 = rand.nextInt(NUM_ALIEN_bullet);
    			// そのエイリアンが生きていればビーム発射
    			/*if (aliens[n].isAlive()) {
                // 発射されていないビームを見つける
                // 1つ見つけたら発射してbreakでループをぬける
                for (int j = 0; j < NUM_BEAM; j++) {
                    if (beams[j].isInStorage()) {
                        // ビームが保管庫にあれば発射できる
                        // ビームの座標をエイリアンの座標にセットすれば発射される
                        Point pos = aliens[n].getPos();
                        beams[j].setPos(pos.x + aliens[n].getWidth() / 2, pos.y);
                        break;
                    }
                }
            }*/
    			if (enemy_bullet[n1].isAlive()) {
    				// 発射されていないビームを見つける
    				// 1つ見つけたら発射してbreakでループをぬける
    				//for (int j = 0; j < NUM_BEAM/2; j++) {
    				for (int j = 0; j < BOS_BEAM / 2; j++) {
    					if (beams[j].isInStorage()) {
    						// ビームが保管庫にあれば発射できる
    						// ビームの座標をエイリアンの座標にセットすれば発射される
    						Point pos = enemy_bullet[n1].getPos();
    						beams[j].setPos(pos.x + enemy_bullet[n1].getWidth() / 2, pos.y);
    						break;
    					}
    				}
    			}
    		}
        }
    	for (int i = 0; i < NUM_BEAM; i++) {
    		//モブの攻撃
        	// ランダムにエイリアンを選ぶ
        	/*int n = rand.nextInt(NUM_ALIEN);*/
        	int n1 = rand.nextInt(NUM_MOB_ENEMY);
            if (mob_enemy[n1].isAlive()) {
                // 発射されていないビームを見つける
                // 1つ見つけたら発射してbreakでループをぬける
                for (int j = 0; j < NUM_BEAM; j++) {
                    if (beams[j].isInStorage()) {
                        // ビームが保管庫にあれば発射できる
                        // ビームの座標をエイリアンの座標にセットすれば発射される
                        Point pos = mob_enemy[n1].getPos();
                        beams[j].setPos(pos.x + mob_enemy[n1].getWidth() / 4, pos.y);
                        break;
                    }
                }
            }

        }
    }

    /**
     * 衝突検出
     *
     */
    private void collisionDetection() {
        // エイリアンと弾の衝突検出
    	if(aliens[0].boss_flag == 1){
        for (int i = 0; i < NUM_ALIEN; i++) {
            for (int j = 0; j < NUM_SHOT; j++) {
                if (aliens[i].collideWith(shots[j])) {
                    // i番目のエイリアンとj番目の弾が衝突
                    // 爆発エフェクト生成
                    explosion = new Explosion(aliens[i].getPos().x, aliens[i].getPos().y);
                    // HPが減っていきHPが0になったらエイリアンは死ぬ
                    HP--;
                    if(HP < 0){
                    	// 死亡時の処理
                        aliens[i].die();
                        for(int kk = 0; kk < NUM_ALIEN_bullet; kk++){
                        	enemy_bullet[kk].die();
                        }

                        for(int kk = 0; kk < NUM_BEAM; kk++){
                        	beams[kk].die();
                        }

                        HP=farstHP;
                        // 断末魔
                        WaveEngine.play(1);

                        repaint();
                        int sleep = 0;
                        while(sleep > 100){
                        //move();
                        	try {
								Thread.sleep(20);
								sleep++;
							} catch (InterruptedException e) {
								// TODO 自動生成された catch ブロック
								e.printStackTrace();
							}

                        }
                        initGame();
                    }
                                            // 弾は保管庫へ（保管庫へ送らなければ貫通弾になる）
                    shots[j].store();
                    // エイリアンが死んだらもうループまわす必要なし
                    break;

                }
            }
        }
    	}
        for (int i = 0; i < NUM_MOB_ENEMY; i++) {//******************************************
            for (int j = 0; j < NUM_SHOT; j++) {
                if (mob_enemy[i].collideWith(shots[j])) {
                    // i番目のエイリアンとj番目の弾が衝突
                    // 爆発エフェクト生成
                    //explosion = new Explosion(mob_enemy[i].getPos().x, mob_enemy[i].getPos().y);
                    mob_enemy[i].HP--;
                    if(mob_enemy[i].HP <= 0){
                    	 mob_enemy[i].die();
                    	 WaveEngine.play(1);
                    }
                    
                    // 弾は保管庫へ（保管庫へ送らなければ貫通弾になる）
                    shots[j].store();
                }
            }
        }

        // プレーヤーとビームの衝突検出
        for (int i = 0; i < NUM_BEAM; i++) {
            if (player.collideWith(beams[i])) {
                // 爆発エフェクト生成
                //explosion = new Explosion(player.getPos().x, player.getPos().y);
                // 爆発音
                WaveEngine.play(0);
                // プレーヤーとi番目のビームが衝突
                // ビームは保管庫へ
                beams[i].store();
                // ゲームオーバー
                initGame();
            }
        }
    }

    /**
     * 描画処理
     *
     * @param 描画オブジェクト
     */
    public void paintComponent(Graphics g) {
    	super.paintComponent(g);
        //Graphics2D g2 = (Graphics2D) g;


        // 背景を黒で塗りつぶす


        //背景を書く
    	if(MainPanel.frag_title == 1){
	        back.draw(g, count % (BACK_WIDTH / 2));



	        // エイリアンを描画
	        for (int i = 0; i < NUM_ALIEN; i++) {
	            aliens[i].draw(g);
	        }
	        // 砲台を描画
	        for (int i = 0; i < NUM_ALIEN_bullet; i++) {
	            enemy_bullet[i].draw(g);
	        }
	        // 弾を描画
	        for (int i = 0; i < NUM_SHOT; i++) {
	            shots[i].draw(g);
	        }

	        // プレイヤーを描画
	        player.draw(g);

	        for (int i = 0; i < NUM_MOB_ENEMY; i++) {//**********************************
	            mob_enemy[i].draw(g);
	        }

	        // ビームを描画
	        for (int i = 0; i < NUM_BEAM; i++) {
	            beams[i].draw(g);
	        }

	        // 爆発エフェクトを描画
	        /*
	        if (explosion != null) {
	            explosion.draw(g);
	        }
	        */
	        hpbar.draw(g, farstHP, HP);

	        /*
	        g.drawRect(player.x + Player.hitjud[0],
	        		player.y + Player.hitjud[1],
	        		Player.hitjud[2],
	        		Player.hitjud[3]);
	        */

	        //lockon.draw(g);

    	}else {
    		back.draw2(g);
    		}

    }
    // タイトル設定とか
    public void keyTyped(KeyEvent e) {
    }

    /**
     * キーが押されたらキーの状態を「押された」に変える
     *
     * @param e キーイベント
     */
    public void keyPressed(KeyEvent e) {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_UP) {
        	upPressed 	= true;
        }
        if (key == KeyEvent.VK_DOWN) {
        	downPressed = true;
        }

        if (key == KeyEvent.VK_RIGHT) {
        	rightPressed = true;
        }
        if (key == KeyEvent.VK_LEFT) {
            leftPressed = true;
        }

        if (key == KeyEvent.VK_SPACE) {
            firePressed 	= true;
        }
    }

    /**
     * キーが離されたらキーの状態を「離された」に変える
     *
     * @param e キーイベント
     */
    public void keyReleased(KeyEvent e) {
        int key = e.getKeyCode();

        if (key == KeyEvent.VK_UP) {
        	upPressed = false;
        }
        if (key == KeyEvent.VK_DOWN) {
        	downPressed = false;
        }
        if (key == KeyEvent.VK_RIGHT) {
        	rightPressed = false;
        }
        if (key == KeyEvent.VK_LEFT) {
        	leftPressed = false;
        }
        if (key == KeyEvent.VK_SPACE) {
            firePressed 	= false;
        }
    }

    double flgchanger(boolean flgplus, boolean flgmnas){
    	double i = 0;

    	if(flgplus == true){
    		i = 1;
    	}
    	else if(flgmnas == true){
    		i = -1;
    	}

    	return i;
    }
}