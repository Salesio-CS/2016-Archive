import java.awt.Graphics;
import java.awt.Image;
import java.awt.Point;
import java.awt.Rectangle;
import java.net.URL;

import javax.swing.ImageIcon;

/*
 * Created on 2005/02/09
 *
 */

/**
 * プレイヤークラス
 *
 * @author mori
 *
 */
public class Player {
    // 移動スピード
    private static final int SPEED = 10;

    // プレイヤーの位置（x座標）
    public int x;
    // プレイヤーの位置（y座標）
    public int y;
    // プレイヤーの幅
    private int width;
    // プレイヤーの高さ
    private int height;
    // プレイヤーの画像
    private Image image;

    double vector[] = {0,0};
    double flg_dim[] = {0,0};
    static int[] hitjud =  {100, 18, 48, 18}; //当たり判定一覧


    private String obname = "image/player.gif";

    URL url = this.getClass().getClassLoader().getResource(obname);


    // メインパネルへの参照
    private MainPanel panel;

    public Player(int x, int y, MainPanel panel) {
        this.x = x;
        this.y = y;
        this.panel = panel;

        // イメージをロード
        loadImage();
    }

    /**
     * プレイヤーを移動する
     *
     * @param dir 移動方向
     */
    public void move(double vect_x,double vect_y) {

    	if(flg_dim[0] != vect_x || flg_dim[1] != vect_y){

    		/*

    		double rad = Vectol.Radian(vect_x,vect_y);

    		vector[0] = Math.sin(rad);
    		if(vect_y > 0){
    			vector[1] = Math.cos(rad);
    		}else if(vect_y < 0){
    			vector[1] = Math.cos(rad) * -1;
    		}

    		*/

    		vector[0] =vect_x * SPEED;
    		vector[1] =vect_y * SPEED;

    		System.out.println(vector[0] + " " + vector[1] + " ");
    		flg_dim[0] = vect_x;
    		flg_dim[1] = vect_y;
    	}

    	y -= (int)vector[0];
		x += (int)vector[1];

		// 画面の外に出ていたら中に戻す
		if (x < 0) {
			x = 0;
		}
		if (x > MainPanel.WIDTH - width / 2) {
			x = MainPanel.WIDTH - width / 2;
		}

		if (y < 0) {
			y = 0;
		}
		if (y > MainPanel.HEIGHT - height / 2) {
			y = MainPanel.HEIGHT - height / 2;
		}
    }

    /**
     * プレイヤーとビームの衝突を判定する
     *
     * @param beam 衝突しているか調べるビームオブジェクト
     * @return 衝突していたらtrueを返す
     */
    public boolean collideWith(Beam beam) {
        // プレイヤーの矩形を求める 当たり判定

        Rectangle rectPlayer = new Rectangle(x + hitjud[0], y + hitjud[1], hitjud[2], hitjud[3]);
        // ビームの矩形を求める
        Point pos = beam.getPos();
        Rectangle rectBeam = new Rectangle(pos.x + beam.hit[0], pos.y + beam.hit[1],
                beam.hit[2], beam.hit[3]);

        // 矩形同士が重なっているか調べる
        // 重なっていたら衝突している
        return rectPlayer.intersects(rectBeam);
    }

    /**
     * プレイヤーを描画する
     *
     * @param g 描画オブジェクト
     */
    public void draw(Graphics g2) {
        g2.drawImage(image, x, y, width / 2, height / 2,null);
    }

    /**
     * プレイヤーの位置を返す
     *
     * @return プレイヤーの位置座標
     */
    public Point getPos() {
        return new Point(x, y);
    }

    /**
     * プレイヤーの幅を返す
     *
     * @param width プレイヤーの幅
     */
    public int getWidth() {
        return width / 2;
    }

    /**
     * プレイヤーの高さを返す
     *
     * @return height プレイヤーの高さ
     */
    public int getHeight() {
        return height / 2;
    }

    /**
     * イメージをロードする
     *
     */
    private void loadImage() {
        // プレイヤーのイメージを読み込む
        // ImageIconを使うとMediaTrackerを使わなくてすむ

        image = (url != null) ? new ImageIcon(url).getImage()
        		:new ImageIcon(obname).getImage();

        // 幅と高さをセット
        width = image.getWidth(panel);
        height = image.getHeight(panel);
    }
}
