import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;


public class HPLayer {
	int fullHP;
	int nowHP;
	int y_HP;

	static final Point HPbar = new Point(300,10);

	private MainPanel panel;

	int p_HP = HPbar.x;

	HPLayer(MainPanel panel){
		this.panel = panel;
		y_HP = HPbar.x;
	}

	void draw(Graphics g2, int farstHP,int nowHP){
		//ボスが出てくるまで放置
		if(panel.aliens[0].boss_flag == 1){
			g2.setColor(Color.GRAY);
			g2.fillRect(1200, 100, HPbar.x, HPbar.y);
			if(y_HP != nowHP){
				p_HP = percent((double)farstHP,(double)nowHP);
				y_HP = nowHP;
			}
			g2.setColor(Color.RED);
			g2.fillRect(1200, 100, p_HP, HPbar.y);
		}
	}

	int percent(double f_HP,double n_HP){
		//計算
		double i = (double)(n_HP / f_HP) * HPbar.x;
		//System.out.println(n_HP + " " + f_HP + " " + i);
		return (int)i;
	}
}
