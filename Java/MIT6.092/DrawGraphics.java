import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

public class DrawGraphics {
    ArrayList<BouncingBox> boxes;

    /** Initializes this class for drawing. */
    public DrawGraphics() {
        boxes = new ArrayList<>(); // 必须要先初始化boxes
        BouncingBox box1 = new BouncingBox(200, 50, Color.RED);
        BouncingBox box2 = new BouncingBox(200, 50, Color.BLUE);
        BouncingBox box3 = new BouncingBox(200, 50, Color.GREEN);
        box1.setMovementVector(1,0);
        box2.setMovementVector(-1,0);
        box3.setMovementVector(0,1);
        boxes.add(box1);
        boxes.add(box2);
        boxes.add(box3);
    }

    /** Draw the contents of the window on surface. Called 20 times per second. */
    public void draw(Graphics surface) {
        surface.drawLine(50, 50, 250, 250);
        surface.drawRect(50, 50, 10, 10);
        surface.drawOval(80, 80, 10, 10);
        for (BouncingBox box : boxes) {
            box.draw(surface);
        }
    }
} 