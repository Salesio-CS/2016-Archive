import java.awt.Graphics;
import java.awt.Image;
import java.net.URL;

import javax.swing.ImageIcon;

public class Back {

    private int x;
    private int y;
    private int width;
    private int height;
    private Image image;
    private MainPanel panel;

    String obname = "image/sabaku1.gif";

    URL url = this.getClass().getClassLoader().getResource(obname);

    //起動準備


    {
    	switch(MainPanel.frag_title){
    	case 0:obname = "image/title.gif";break;
    	case 1:obname = "image/sabaku1.gif";break;
    	}
    	url = this.getClass().getClassLoader().getResource(obname);
    }

    public Back(int x, int y, MainPanel panel) {
    	this.x = x;
    	this.y = y;
        loadImage();
    }

    //イメージロード

    private void loadImage() {
        //ImageIcon icon = new ImageIcon(obname);
    	//System.out.printf("url = %s",url);

    	image = (url != null)
        		? new ImageIcon(url).getImage()
        		: new ImageIcon(obname).getImage();

        width = image.getWidth(panel);
        height = image.getHeight(panel);
    }

    //描画

    public void draw(Graphics g2,int count) {

        g2.drawImage(image, 0, 0, x, y, count, 0, (width / 2) + count, height, null);
    }
    public void draw2(Graphics g2) {

        g2.drawImage(image, 0,0,x,y,null);
    }


    public int backwidth(){
    	//自分の幅を返す
    	return width;
    }
}

