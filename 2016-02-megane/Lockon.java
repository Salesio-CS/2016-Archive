import java.awt.Graphics;
import java.awt.Point;

public class Lockon {

	Point start = new Point(), end = new Point(), distance = new Point();
	Point target = new Point(),jud = new Point();

	int speed;

	double tanjent;
	Lockon(MainPanel Panel, int st_x,int st_y){

		start.x = 200;
		start.y = 200;
		target.x = Panel.player.getWidth();
		target.y = Panel.player.getHeight();
		
		jud.x = Player.hitjud[0] + Player.hitjud[2] / 2;
		jud.y = Player.hitjud[1] + Player.hitjud[3] / 2;
		Roading(st_x,st_y);

	}

	void tance(int x0,int y0,int x1,int y1){

		distance.x = x1 - x0;
		distance.y = y1 - y0;
	}
	
	void update (int st_x,int st_y){
		if(!(st_x == start.x && st_y == start.y)){
			Roading(st_x,st_y);
		}
			
	}
	
	void Roading( int st_x, int st_y){
		end.x = st_x + jud.x;
		end.y = st_y + jud.y;
	}

	
	 void draw(Graphics g){
		g.drawLine(start.x,start.y,end.x,end.y);
		
	}
}
