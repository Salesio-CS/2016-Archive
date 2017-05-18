import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.net.URL;
import java.util.Random;

import javax.swing.ImageIcon;

/*
 * Created on 2005/03/19
 *
 */

/**
 * ビームクラス
 *
 * @author mori
 *
 */
public class Beam {
    // ビームのスピード
    private static final int SPEED = 5;
    // ビームの保管座標（画面に表示されない場所）
    private static final Point STORAGE = new Point(-200, -200);

    // ビームの位置（x座標）
    private int x;
    // ビームの位置（y座標）
    private int y;
    // ビームの幅
    private int width;
    // ビームの高さ
    private int height;
    // ビームの画像
    private Image image;

    // メインパネルへの参照
    private MainPanel panel;

    private Random rand;
    
    public int hit[] = {
    		5,5,0,0};

    int randam;

    String obname = "image/enemy_wepon.gif";

    URL url = this.getClass().getClassLoader().getResource(obname);

    public Beam(MainPanel panel) {
        x = STORAGE.x;
        y = STORAGE.y;
        this.panel = panel;

        rand = new Random();

        randam = rand.nextInt(6);

        // イメージをロード
        loadImage();
        
        hit[2] = width - 10;
        hit[3] = height - 10;
    }

    /**
     * ビームを移動する
     */
    public void move() {
        // 保管庫に入っているなら何もしない
        if (isInStorage())
            return;

        // ビームはx方向にしか移動しない
        x -= SPEED + randam;
        // 画面外のビームは保管庫行き
        if (x < -100) {
            store();
        }
    }

    /**
     * ビームの位置を返す
     *
     * @return ビームの位置座標
     */
    public Point getPos() {
        return new Point(x, y);
    }

    /**
     * ビームの位置をセットする
     *
     * @param x ビームのx座標
     * @param y ビームのy座標
     */
    public void setPos(int x, int y) {
        this.x = x;
        this.y = y;
    }

    /**
     * ビームの幅を返す。
     *
     * @param width ビームの幅。
     */
    public int getWidth() {
        return width;
    }

    /**
     * ビームの高さを返す。
     *
     * @return height ビームの高さ。
     */
    public int getHeight() {
        return height;
    }

    /**
     * ビームを保管庫に入れる
     */
    public void store() {
        x = STORAGE.x;
        y = STORAGE.y;
    }

    /**
     * ビームが保管庫に入っているか
     *
     * @return 入っているならtrueを返す
     */
    public boolean isInStorage() {
        if (x == STORAGE.x && y == STORAGE.y)
            return true;
        return false;
    }

    /**
     * ビームを描画する
     *
     * @param g 描画オブジェクト
     */
    public void draw(Graphics g2) {
        // �r�[����`�悷��
        g2.drawImage(image, x, y, null);
    }

    /**
     * イメージをロードする
     *
     */
    private void loadImage() {
        //ImageIcon icon = new ImageIcon(getClass().getResource("image/enemy_wepon.gif"));
        //image = icon.getImage();

    	//イメージロード

    	if (url != null){
    		image = new ImageIcon(url).getImage();
    	} else {
    		image = new ImageIcon(obname).getImage();
    	}
    	/*
        image = (url != null)
        		? new ImageIcon(url).getImage()
        		: new ImageIcon(obname).getImage();
		*/
        // 幅と高さをセット
        width = image.getWidth(panel);
        height = image.getHeight(panel);
    }

    public void die() {
        setPos(STORAGE.x,STORAGE.y);
    }
}