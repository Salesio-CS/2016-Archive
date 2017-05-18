import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.net.URL;

import javax.swing.ImageIcon;

/*
 * Created on 2005/02/17
 *
 */

/**
 * 弾クラス
 *
 * @author mori
 *
 */
public class Shot {
    // 弾のスピード
    private static final int SPEED = 50;
    // 弾の保管座標（画面に表示されない場所）
    private static final Point STORAGE = new Point(-20, -20);

    // 弾の位置（x座標）
    private int x;
    // 弾の位置（y座標）
    private int y;
    // 弾の幅
    private int width;
    // 弾の高さ
    private int height;
    // 弾の画像
    private Image image;
    // 読み込みアドレス
    private String obname = "image/shot.gif";
    URL url = this.getClass().getClassLoader().getResource(obname);


    // メインパネルへの参照
    private MainPanel panel;

    public Shot(MainPanel panel) {
        x = STORAGE.x;
        y = STORAGE.y;
        this.panel = panel;

        // イメージをロード
        loadImage();
    }

    /**
     * 弾を移動する
     *
     */
    public void move() {
        // 保管庫に入っているなら何もしない
        if (isInStorage())
            return;

        // 弾はx方向にしか移動しない
        x += SPEED;
        // 画面外の弾は保管庫行き
        if (x > 1920) {
            store();
        }
    }

    /**
     * 弾の位置を返す
     *
     * @return 弾の位置座標
     */
    public Point getPos() {
        return new Point(x, y);
    }

    /**
     * 弾の位置をセットする
     *
     * @param x 弾のx座標
     * @param y 弾のy座標
     *
     */
    public void setPos(int x, int y) {
        this.x = x;
        this.y = y + 20;
    }

    /**
     * 弾の幅を返す。
     *
     * @param width 弾の幅。
     */
    public int getWidth() {
        return width;
    }

    /**
     * 弾の高さを返す。
     *
     * @return height 弾の高さ。
     */
    public int getHeight() {
        return height;
    }

    /**
     * 弾を保管庫に入れる
     *
     */
    public void store() {
        x = STORAGE.x;
        y = STORAGE.y;
    }

    /**
     * 弾が保管庫に入っているか
     *
     * @return 入っているならtrueを返す
     */
    public boolean isInStorage() {
        if (x == STORAGE.x && y == STORAGE.x)
            return true;
        return false;
    }

    /**
     * 弾を描画する
     *
     * @param g 描画オブジェクト
     */
    public void draw(Graphics g) {
        // 弾を描画する
        g.drawImage(image, x, y, null);
    }

    /**
     * イメージをロードする
     *
     */
    
    private void loadImage() {
    	//System.out.printf("url = %s\n",url);

    	
    	image = (url != null) ? new ImageIcon(url).getImage()
        		:new ImageIcon(obname).getImage();

        width = image.getWidth(panel);
        height = image.getHeight(panel);
    }

}