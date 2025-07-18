import java.awt.*;

public class Oval implements Sprite{
    private int longR;
    private int shortR;
    private Color color;
    public Oval(int longR, int shortR, Color color) {
        this.longR = longR;
        this.shortR = shortR;
        this.color = color;
    }
    public int getWidth() {
        return shortR;
    }

    public int getHeight() {
        return longR;
    }
    @Override
    public void draw(Graphics surface, int leftX, int topY) {
        // Draw the object
        surface.setColor(color);
        surface.fillOval(leftX, topY, shortR, longR);
        surface.setColor(Color.BLACK);
        ((Graphics2D) surface).setStroke(new BasicStroke(3.0f));
        surface.drawOval(leftX, topY, shortR, longR);
    }
}
