
	import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.net.URL;

import javax.swing.ImageIcon;


	/*
	 * Created on 2005/03/09
	 *
	 */

	/**
	 * �G�C���A���N���X
	 *
	 * @author mori
	 *
	 */
public class enemy_bullet {
	   // エイリアンの移動範囲
    private static final int MOVE_WIDTH = 150;
    // エイリアンの墓（画面に表示されない場所）
    private static final Point TOMB = new Point(-1500, -1500);

    // 移動スピード
    private int speed;

    // エイリアンの位置（x座標）
    public int x;
    // エイリアンの位置（y座標）
    public int y;
    // エイリアンの幅
    public int width;
    // エイリアンの高さ
    public int height;
    // エイリアンの画像
    private Image image;

    private int hitjud[] = {0,0,0,0};

    // エイリアンの移動範囲
    private int left;
    private int right;

    //private String obname = "image/tank_tama.gif";
    private String obname = "image/brank.gif";

    URL url = this.getClass().getClassLoader().getResource(obname);

    // エイリアンが生きてるかどうか
    private boolean isAlive;

    // メインパネルへの参照
    private MainPanel panel;

    public enemy_bullet(int x, int y, int speed, MainPanel panel) {
        this.x = x + 1000;
        this.y = y + 100;
        this.speed = speed;
        this.panel = panel;

        // エイリアンの初期位置から移動範囲を求める
        left = y;
        right = y + MOVE_WIDTH;

        isAlive = true;

        // イメージをロード
        loadImage();

        hitjud[2] = width;
        hitjud[3] = height;
    }

    /**
     * エイリアンを移動する
     *
     */
    public void move() {


    	y += speed;

        // 移動範囲を超えていたら反転移動
    	if (!(((y > left) && (y < right)))) {
            speed = -speed;
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
        Rectangle rectAlien = new Rectangle(x + hitjud[0], y + hitjud[1], hitjud[2], hitjud[3]);
        // 弾の矩形を求める
        Point pos = shot.getPos();
        Rectangle rectShot = new Rectangle(pos.x, pos.y,
                shot.getWidth(), shot.getHeight());

        // 矩形同士が重なっているか調べる
        // 重なっていたら衝突している
        return rectAlien.intersects(rectShot);
    }

    //RamAttack

    /**
     * エイリアンが死ぬ、墓へ移動
     *
     */
    public void die() {
        setPos(TOMB.x, TOMB.y);
        isAlive = false;
    }

    /**
     * エイリアンの幅を返す
     *
     * @param width エイリアンの幅
     */
    public int getWidth() {
        return width;
    }

    public int getx(){
    	return x;
    }

    public int gety(){
    	return y;
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
        g.drawImage(image, x, y, width, height, null);
    }

    /**
     * イメージをロードする
     *
     */
    private void loadImage() {
        // エイリアンのイメージを読み込む
        // ImageIconを使うとMediaTrackerを使わなくてすむ
    	/*
        ImageIcon icon = new ImageIcon(getClass()
                .getResource("image/tank_tama.gif"));
        image = icon.getImage();
        */

        image = (url != null) ? new ImageIcon(url).getImage()
        		:new ImageIcon(obname).getImage();

        // 幅と高さをセット
        width = image.getWidth(panel);
        height = image.getHeight(panel);
    }
}
