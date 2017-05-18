import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;

import javax.swing.ImageIcon;

/*
 * Created on 2005/03/09
 *
 */

/**
 * エイリアンクラス
 *
 * @author mori
 *
 */
public class Mob_enemy {

    // エイリアンの墓（画面に表示されない場所)
    private static final Point TOMB = new Point(-2000, -1000);

    private static final Point STORAGE = new Point(1100, -200);
    // 移動スピード
    private int speed;

    // エイリアンの位置（x座標）
    private int x;
    // エイリアンの位置（y座標）
    private int y;
    // エイリアンの幅
    private int width;
    // エイリアンの高さ
    private int height;
    // エイリアンの画像
    private Image image;

    public int HP = 20;
    
    //判定の設定

    public double[][] hitjud = {
    		{0.100, 0.489, 0.757, 0.311},
    		{0.587, 0.032, 0.107, 0.516}
    		//{0.032, 0.587, 0.516, 0.107}
    		};
    public int hit[][] = {
    		{0,0,0,0},
    		{0,0,0,0}
    		};
    public boolean moveflg[] = {false, false, false};//r,l,line

    int time=0;
    // エイリアンが生きてるかどうか
    private boolean isAlive;

    // メインパネルへの参照
    private MainPanel panel;

    public Mob_enemy(MainPanel panel) {
        x = STORAGE.x;
        y = STORAGE.y;
        speed = 1;
        this.panel = panel;
        
        // イメージをロード
        
        loadImage();

        isAlive = true;
        //当たり判定代入
        for(int i = 0;i < 2;i++){
        	hit[i][0] = (int)Math.round(hitjud[i][0] * width);
        	hit[i][1] = (int)Math.round(hitjud[i][1] * height);
        	hit[i][2] = (int)Math.round(hitjud[i][2] * width);
        	hit[i][3] = (int)Math.round(hitjud[i][3] * height);
        }

      
        

    }
    
    /**
     * エイリアンを移動する
     *
     */
    
    public void move(){
    	if(moveflg[0] == true){
    		y += speed;
    		if(y%2==0){
    			x -= speed;
    		}
    	}
    	if(moveflg[1] == true){
    		y += speed;
    		if(y%2==0){
    			x += speed;
    		}
    	}
    	if(moveflg[2] == true){
    		y += speed;
    	}
    	
    	//範囲外に出たら殺す
    	
    	if(x > MainPanel.WIDTH || y >MainPanel.HEIGHT){
    		die();
    	}


    }

    /**
     * エイリアンと弾の衝突を判定する
     *
     * @param shot 衝突しているか調べる弾オブジェクト
     * @return 衝突していたらtrueを返す
     */
    
    public boolean collideWith(Shot shot) {
         // エイリアンの矩形を求める
        Rectangle rectAlien_alfa 	= new Rectangle(x + hit[0][0], y + hit[0][1], hit[0][2], hit[0][3]);//下部分の判定
        Rectangle rectAlien_bravo 	= new Rectangle(x + hit[1][0], y + hit[1][1], hit[1][2], hit[1][3]);//上部分の判定
        // 弾の矩形を求める
        Point pos = shot.getPos();
        Rectangle rectShot = new Rectangle(pos.x, pos.y,
                shot.getWidth(), shot.getHeight());

        // 矩形同士が重なっているか調べる
        // 重なっていたら衝突している
        boolean answer = ((rectAlien_alfa.intersects(rectShot)) || (rectAlien_bravo.intersects(rectShot)));
        return answer;
    }

    /**
     * エイリアンが死ぬ、墓へ移動
     *
     */
    public void die() {
        setPos(TOMB.x, TOMB.y);
        	isAlive = false;
        	//フラグいじって動かなくする
        	for(int i = 0;i < 2;i++){
        		moveflg[i] = false;
        	}
    }

    /**
     * エイリアンの幅を返す
     *
     * @param width エイリアンの幅
     */
    public int getWidth() {
        return width;
    }

    /**
     * エイリアンの高さを返す
     *
     * @return height エイリアンの高さ
     */
    public int getHeight() {
        return height;
    }

    /**
     * エイリアンの位置を返す
     *
     * @return エイリアンの位置座標
     */
    public Point getPos() {
        return new Point(x, y);
    }

    /**
     * エイリアンの位置を(x,y)にセットする
     *
     * @param x 移動先のx座標
     * @param y 移動先のy座標
     */
    public void setPos(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * エイリアンが生きているか
     *
     * @return 生きていたらtrueを返す
     */
    public boolean isAlive() {
        return isAlive;
    }

    /**
     * エイリアンを描画する
     *
     * @param g 描画オブジェクト
     */
    public void draw(Graphics g) {
        g.drawImage(image, x, y, width,height,null);
        //g.drawRect(x + hit[0][0], y + hit[0][1], hit[0][2], hit[0][3]);
        //g.drawRect(x + hit[1][0], y + hit[1][1], hit[1][2], hit[1][3]);
    }

    /**
     * イメージをロードする
     *
     */
    private void loadImage() {
        // エイリアンのイメージを読み込む
        // ImageIconを使うとMediaTrackerを使わなくてすむ
        ImageIcon icon = new ImageIcon(getClass()
                .getResource("image/sensya.gif"));
        image = icon.getImage();

        // 幅と高さをセット
        width = image.getWidth(panel) / 2;
        height = image.getHeight(panel) / 2;
    }
}