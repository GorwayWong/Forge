import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

public class DrawGraphics {
    ArrayList<Mover> movers;

    /** Initializes this class for drawing. */
    public DrawGraphics() {
        movers = new ArrayList<>();
        Rectangle rec = new Rectangle(10,10,Color.red);
        Bouncer bouncer = new Bouncer(10,10,rec);
        bouncer.setMovementVector(-3,0);
        Oval oval = new Oval(20,10,Color.green);
        Bouncer bouncer2 = new Bouncer(40,40,oval);
        bouncer2.setMovementVector(-3,1);
        movers.add(bouncer);
        movers.add(bouncer2);

        Rectangle rec2 = new Rectangle(30,30,Color.BLUE);
        Oval oval2 = new Oval(40,40,Color.BLUE);
        StraightMover straightMover1 = new StraightMover(60, 60, rec2);
        StraightMover straightMover2 = new StraightMover(100, 200, oval2);
        movers.add(straightMover1);
        movers.add(straightMover2);
    }

    /** Draw the contents of the window on surface. */
    public void draw(Graphics surface) {
        for (Mover b : movers) {
            b.draw(surface);
        }
    }
}
