// package OnlineJudge;

import com.sun.tools.javac.Main;

import java.awt.geom.Line2D;
import java.io.*;
import java.awt.*;
import java.util.*;
import javax.swing.*;
import java.awt.event.*;
import java.io.Serializable;

class Image implements Serializable {
    ArrayList<Contents> contentList;
    Color backgroundColour;
    Image(){
        this.contentList=new ArrayList<Contents>();
        this.backgroundColour=new Color(255,255,255);
    }
    public void imageAppend(Contents contents){
        this.contentList.add(contents);
    }
    public Contents imageCtrlZ(){
        if(this.contentList.size()==0){
            return null;
        }
        Contents temp=this.contentList.get(this.contentList.size()-1);
        this.contentList.remove(this.contentList.size()-1);
        return temp;
    }
    public void imageChangeBackgroundColour(Color backgroundColour){
        this.backgroundColour=backgroundColour;
    }
}

abstract class Contents{
    public abstract void draw(Graphics2D graphics2D);
    public abstract Shape getShape();
    public abstract void setColour(Color colour);
    public abstract void setFilling(boolean filling);
    public abstract void setShape(Shape shape);
}

class PainterShapes extends Contents implements Serializable{
    Shape shape;
    Color colour;
    boolean filling;

    PainterShapes(Shape shape,Color colour,boolean filling){
        this.shape=shape;
        this.colour=colour;
        this.filling=filling;
    }

    @Override
    public void draw(Graphics2D graphics2D) {
        graphics2D.setColor(this.colour);
        graphics2D.draw(this.shape);
    }

    @Override
    public void setShape(Shape shape) {
        this.shape=shape;
    }

    @Override
    public Shape getShape() {
        return this.shape;
    }

    @Override
    public void setColour(Color colour) {
        this.colour=colour;
    }

    @Override
    public void setFilling(boolean filling) {
        this.filling=filling;
    }
}

class PainterString extends Contents implements Serializable{
    String content;
    Font font;
    Color colour;
    float x;
    float y;

    PainterString(String content,Font font,Color colour,float x,float y){
        this.content=content;
        this.font=font;
        this.colour=colour;
        this.x=x;
        this.y=y;
    }

    @Override
    public void draw(Graphics2D graphics2D) {
        graphics2D.setColor(this.colour);
        graphics2D.setFont(this.font);
        graphics2D.drawString(this.content,x,y);
    }

    @Override
    public Shape getShape() {
        return null;
    }

    @Override
    public void setShape(Shape shape) {

    }

    @Override
    public void setColour(Color colour) {
        this.colour=colour;
    }

    @Override
    public void setFilling(boolean filling) {

    }
}

class PainterGraph extends Contents implements Serializable{
    String shape;
    Color colour;
    boolean filling;
    float x;
    float y;
    float a;
    float b;

    PainterGraph(String type,Color colour,float x,float y,float a,float b,boolean filling){
        this.shape=type;
        this.colour=colour;
        this.x=x;
        this.y=y;
        this.a=a;
        this.b=b;
        this.filling=filling;
    }


    @Override
    public void draw(Graphics2D graphics2D) {
        if(this.shape.equals("Line")){
            graphics2D.setColor(this.colour);
            graphics2D.drawLine((int)this.x,(int)this.y,(int)this.a,(int)this.b);
        }
        else if(this.shape.equals("Round")){
            graphics2D.setColor(this.colour);
            if(this.filling){
                graphics2D.fillOval((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a),(int)Math.abs(this.y-this.b));
//                graphics2D.fillOval((int)(this.x+this.a)/2,(int)(this.y+this.b)/2,(int)Math.abs(this.x-this.a)/2,(int)Math.abs(this.y-this.b)/2);
            }
            else{
                graphics2D.drawOval((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a),(int)Math.abs(this.y-this.b));
//                graphics2D.drawOval((int)(this.x+this.a)/2,(int)(this.y+this.b)/2,(int)Math.abs(this.x-this.a)/2,(int)Math.abs(this.y-this.b)/2);
            }
        }
        else if(this.shape.equals("Square")){
            graphics2D.setColor(this.colour);
            if(this.filling){
                graphics2D.fillRect((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a),(int)Math.abs(this.y-this.b));
//                graphics2D.fillRect((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a)/2,(int)Math.abs(this.y-this.b)/2);
            }
            else{
                graphics2D.drawRect((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a),(int)Math.abs(this.y-this.b));
//                graphics2D.drawRect((int)Math.min(this.x,this.a),(int)Math.min(this.y,this.b),(int)Math.abs(this.x-this.a)/2,(int)Math.abs(this.y-this.b)/2);
            }
        }
    }

    @Override
    public Shape getShape() {
        return null;
    }

    @Override
    public void setShape(Shape shape) {

    }

    @Override
    public void setColour(Color colour) {
        this.colour=colour;
    }

    @Override
    public void setFilling(boolean filling) {
        this.filling=filling;
    }
}

class DrawingMouseListener extends MouseAdapter{
    DrawingBoard parent;
    DrawingMouseListener(DrawingBoard parent){
        this.parent=parent;
    }
}
class DrawingMouseMovingListener extends MouseMotionAdapter{
    DrawingBoard parent;
    DrawingMouseMovingListener(DrawingBoard parent){
        this.parent=parent;
    }
}

class PenMouseListener extends DrawingMouseListener{

    PenMouseListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        this.parent.edit=true;
        if(this.parent.tempShape!=null) {
            this.parent.image.imageAppend(this.parent.tempShape);
            this.parent.rubbish.clear();
        }

        Line2D l=new Line2D.Double();
        l.setLine(e.getX(), e.getY(), e.getX(), e.getY());
        this.parent.tempShape=new PainterShapes(l,this.parent.currentColour,this.parent.filling);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        Line2D l=(Line2D)(this.parent.tempShape.getShape());
        l.setLine(l.getX1(), l.getY1(), e.getX(), e.getY());
        this.parent.repaint();
    }
}
class PenMouseMotionListener extends DrawingMouseMovingListener{

    PenMouseMotionListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        super.mouseDragged(e);
        if(this.parent.tempShape!=null) {
            Line2D l=(Line2D)(this.parent.tempShape.getShape());
            l.setLine(l.getX1(), l.getY1(), e.getX(), e.getY());
            this.parent.image.imageAppend(this.parent.tempShape);
        }
        Line2D l=new Line2D.Double();
        l.setLine(e.getX(), e.getY(), e.getX(), e.getY());
        this.parent.tempShape=new PainterShapes(l,this.parent.currentColour,this.parent.filling);
        this.parent.repaint();
    }
}

class LineMouseListener extends DrawingMouseListener{

    LineMouseListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        this.parent.edit=true;
        if(this.parent.tempShape!=null) {
            this.parent.tempShape=null;
        }
        this.parent.tempShape=new PainterGraph("Line",this.parent.currentColour,e.getX(),e.getY(),e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(this.parent.tempShape);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        this.parent.tempShape=null;
        this.parent.repaint();
    }
}
class LineMouseMotionListener extends DrawingMouseMovingListener{

    LineMouseMotionListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        float oldX=0;
        float oldY=0;
        if(this.parent.tempShape!=null){
            PainterGraph painterGraph=(PainterGraph)this.parent.tempShape;
            oldX=painterGraph.x;
            oldY=painterGraph.y;
            this.parent.image.contentList.remove(this.parent.image.contentList.size()-1);
        }
        PainterGraph painterGraph=new PainterGraph("Line",this.parent.currentColour,oldX,oldY,e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(painterGraph);
        this.parent.repaint();
    }
}

class RoundMouseListener extends DrawingMouseListener{

    RoundMouseListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        this.parent.edit=true;
        if(this.parent.tempShape!=null) {
            this.parent.tempShape=null;
        }
        this.parent.tempShape=new PainterGraph("Round",this.parent.currentColour,e.getX(),e.getY(),e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(this.parent.tempShape);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        this.parent.tempShape=null;
        this.parent.repaint();
    }
}
class RoundMouseMotionListener extends DrawingMouseMovingListener{

    RoundMouseMotionListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        float oldX=0;
        float oldY=0;
        if(this.parent.tempShape!=null){
            PainterGraph painterGraph=(PainterGraph)this.parent.tempShape;
            oldX=painterGraph.x;
            oldY=painterGraph.y;
            this.parent.image.contentList.remove(this.parent.image.contentList.size()-1);
        }
        PainterGraph painterGraph=new PainterGraph("Round",this.parent.currentColour,oldX,oldY,e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(painterGraph);
        this.parent.repaint();
    }
}

class SquareMouseListener extends DrawingMouseListener{

    SquareMouseListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mousePressed(MouseEvent e) {
        this.parent.edit=true;
        if(this.parent.tempShape!=null) {
            this.parent.tempShape=null;
        }
        this.parent.tempShape=new PainterGraph("Square",this.parent.currentColour,e.getX(),e.getY(),e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(this.parent.tempShape);
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        this.parent.tempShape=null;
        this.parent.repaint();
    }
}
class SquareMouseMotionListener extends DrawingMouseMovingListener{

    SquareMouseMotionListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        float oldX=0;
        float oldY=0;
        if(this.parent.tempShape!=null){
            PainterGraph painterGraph=(PainterGraph)this.parent.tempShape;
            oldX=painterGraph.x;
            oldY=painterGraph.y;
            this.parent.image.contentList.remove(this.parent.image.contentList.size()-1);
        }
        PainterGraph painterGraph=new PainterGraph("Square",this.parent.currentColour,oldX,oldY,e.getX(),e.getY(),this.parent.filling);
        this.parent.image.imageAppend(painterGraph);
        this.parent.repaint();
    }
}

class StringMouseListener extends DrawingMouseListener{

    StringMouseListener(DrawingBoard parent){
        super(parent);
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        JOptionPane jOptionPane=new JOptionPane();

        String inputValue = jOptionPane.showInputDialog(this.parent,"Insert a new String.","Input String",JOptionPane.INFORMATION_MESSAGE);
        if(inputValue==null){
            return;
        }
        Font font=new Font("Sans",10,10);
        PainterString painterString=new PainterString(inputValue,font,this.parent.currentColour,e.getX(),e.getY());
        this.parent.image.contentList.add(painterString);
        this.parent.repaint();
        this.parent.edit=true;
    }
}
class StringMouseMotionListener extends DrawingMouseMovingListener{
    StringMouseMotionListener(DrawingBoard parent){
        super(parent);
    }
}

class DrawingBoard extends JPanel{

    MainWindow parent;

    Image image;
    Stack<Contents> rubbish;
    Contents tempShape;

    Color currentColour;
    Color backgroundColour;

    volatile boolean filling;

    volatile boolean edit;

    DrawingMouseListener drawingMouseListener;
    DrawingMouseMovingListener drawingMouseMovingListener;

    DrawingBoard(MainWindow parent){
        this.edit=false;
        this.filling=true;
        this.image=new Image();
        this.currentColour=new Color(0,0,0);
        this.rubbish=new Stack<Contents>();
        this.parent=parent;
        this.drawingMouseListener=new PenMouseListener(this);
        this.drawingMouseMovingListener=new PenMouseMotionListener(this);
        this.addMouseListener(this.drawingMouseListener);
        this.addMouseMotionListener(this.drawingMouseMovingListener);
    }
    DrawingBoard(MainWindow parent,Image image){
        this.edit=false;
        this.filling=true;
        this.image=image;
        this.currentColour=new Color(0,0,0);
        this.rubbish=new Stack<Contents>();
        this.parent=parent;
        this.drawingMouseListener=new PenMouseListener(this);
        this.drawingMouseMovingListener=new PenMouseMotionListener(this);
        this.addMouseListener(this.drawingMouseListener);
        this.addMouseMotionListener(this.drawingMouseMovingListener);
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D graphics2D=(Graphics2D)g;
        for(Contents contents:image.contentList){
            contents.draw(graphics2D);
        }
        if(this.tempShape!=null){
            this.tempShape.setColour(currentColour);
            this.tempShape.draw(graphics2D);
        }
    }

    public Image getImage(){
        return this.image;
    }
    public void newImage(){
        this.image=new Image();
        this.backgroundColour=Color.WHITE;
        this.setCurrentColour(Color.BLACK);
        this.setBackgroundColour(Color.WHITE);
        this.image.backgroundColour=Color.WHITE;
        this.repaint();
        this.edit=false;
    }
    public void saveImage() throws Exception{
        FileOutputStream fileOutputStream=new FileOutputStream(this.parent.filePath);
        BufferedOutputStream bufferedOutputStream=new BufferedOutputStream(fileOutputStream);
        ObjectOutputStream objectOutputStream=new ObjectOutputStream(bufferedOutputStream);

        objectOutputStream.writeObject(this.image);

        objectOutputStream.close();
        bufferedOutputStream.close();
        fileOutputStream.close();
        this.edit=false;
    }
    public void changeImage(Image newImage){
        this.image=newImage;
        this.setCurrentColour(Color.BLACK);
        this.backgroundColour=this.image.backgroundColour;
        this.setBackground(this.backgroundColour);
        this.repaint();
        this.edit=false;
    }
    public void ctrlZ(){
        if(this.image.contentList.size()==0){
            return;
        }
        Contents temp=this.image.contentList.get(this.image.contentList.size()-1);
        this.rubbish.push(temp);
        this.image.contentList.remove(this.image.contentList.size()-1);
        this.repaint();
    }
    public void ctrlY(){
        if(this.rubbish.empty()){
            return;
        }
        this.image.imageAppend(this.rubbish.pop());
        this.repaint();
    }
    public void setBackgroundColour(Color newBackgrountColour){
        if(newBackgrountColour==null){
            return;
        }
        this.backgroundColour=newBackgrountColour;
        this.setBackground(newBackgrountColour);
    }
    public void setCurrentColour(Color colour){
        if(colour==null){
            return;
        }
        this.currentColour=colour;
    }

    public void changeListener(DrawingMouseListener drawingMouseListener,DrawingMouseMovingListener drawingMouseMovingListener){
        this.removeMouseListener(this.drawingMouseListener);
        this.removeMouseMotionListener(this.drawingMouseMovingListener);
        this.drawingMouseListener=drawingMouseListener;
        this.drawingMouseMovingListener=drawingMouseMovingListener;
        this.addMouseListener(this.drawingMouseListener);
        this.addMouseMotionListener(this.drawingMouseMovingListener);
    }
}

class FileToolBar extends JPanel{

    MainWindow parent;

    FileToolBarListener fileToolBarListener;

    JButton buttonNewFile;
    JButton buttonOpenFile;
    JButton buttonSaveFile;
    JButton buttonSwitchFilling;
    JButton buttonClear;
    JButton buttonUndo;
    JButton buttonRedo;
    JButton buttonInfo;

//    JRadioButton buttonFilling;
//    JRadioButton buttonNotFilling;
//    ButtonGroup buttonGroupFilling;

    FileToolBar(MainWindow parent){
        super(new FlowLayout(FlowLayout.LEFT));
        this.parent=parent;

        this.buttonNewFile=new JButton("New File");
        this.buttonOpenFile=new JButton("Open File");
        this.buttonSaveFile=new JButton("Save File");
        this.buttonSwitchFilling=new JButton("Switch: Filling");
        this.buttonClear=new JButton("Clear");
        this.buttonUndo=new JButton("Undo");
        this.buttonRedo=new JButton("Redo");
        this.buttonInfo=new JButton("Information");

        this.add(this.buttonNewFile);
        this.add(this.buttonOpenFile);
        this.add(this.buttonSaveFile);
        this.add(this.buttonSwitchFilling);
        this.add(this.buttonClear);
        this.add(this.buttonUndo);
        this.add(this.buttonRedo);
        this.add(this.buttonInfo);

        this.addListener();
    }
    protected void addListener(){
        this.fileToolBarListener=new FileToolBarListener(this.parent);
        this.buttonNewFile.addActionListener(this.fileToolBarListener);
        this.buttonOpenFile.addActionListener(this.fileToolBarListener);
        this.buttonSaveFile.addActionListener(this.fileToolBarListener);
        this.buttonSwitchFilling.addActionListener(this.fileToolBarListener);
        this.buttonClear.addActionListener(this.fileToolBarListener);
        this.buttonUndo.addActionListener(this.fileToolBarListener);
        this.buttonRedo.addActionListener(this.fileToolBarListener);
        this.buttonInfo.addActionListener(this.fileToolBarListener);
    }
}
class FileToolBarListener implements ActionListener {

    MainWindow parent;

    FileToolBarListener(MainWindow parent){
        super();
        this.parent=parent;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource().getClass()==JButton.class) {
            JButton button=(JButton)e.getSource();
            if(button.getText().equals("New File")){
                JOptionPane jOptionPane=new JOptionPane();
//                if(!this.parent.drawingBoard.image.contentList.isEmpty()) {
                if(this.parent.drawingBoard.edit) {
                    int saving_before_new_file=jOptionPane.showConfirmDialog(this.parent,"Whether Save This File?","Saving Before New File",JOptionPane.YES_NO_CANCEL_OPTION);
                    // Save old file here.
                    if(saving_before_new_file==0){
                        this.parent.saveFile();
                    }
                    else if(saving_before_new_file==2){
                        return;
                    }
                }
                this.parent.statusAppend("\nCreate New File.");
//                JOptionPane jOptionPane=new JOptionPane();

                String name=jOptionPane.showInputDialog(this.parent,"Name of New File: ","New File",JOptionPane.INFORMATION_MESSAGE);
                if(name!=null){
                    this.parent.createFile(name);
                    this.parent.drawingBoard.newImage();
                }
            }
            else if(button.getText().equals("Open File")){
                JOptionPane jOptionPane=new JOptionPane();
//                if(!this.parent.drawingBoard.image.contentList.isEmpty()) {
                if(this.parent.drawingBoard.edit) {
                    int saving_before_new_file=jOptionPane.showConfirmDialog(this.parent,"Whether Save This File?","Saving Before New File",JOptionPane.YES_NO_CANCEL_OPTION);
                    // Save old file here.
                    if(saving_before_new_file==0){
                        this.parent.saveFile();
                    }
                    else if(saving_before_new_file==2){
                        return;
                    }
                }
                this.parent.statusAppend("\nOpen new file.");
                JFileChooser jFileChooser=new JFileChooser();
                jFileChooser.setDialogTitle("Open File");
                jFileChooser.showOpenDialog(this.parent);
                if(jFileChooser.getSelectedFile()!=null){
                    String path;
                    path=jFileChooser.getSelectedFile().getPath();
                    this.parent.openFile(path);
                }
            }
            else if(button.getText().equals("Clear")){
                this.parent.statusAppend("\nClear.");
                this.parent.drawingBoard.image.contentList.clear();
                this.parent.drawingBoard.rubbish.clear();
                this.parent.drawingBoard.repaint();
            }
            else if(button.getText().equals("Save File")){
                this.parent.statusAppend("\nSave File.");
                this.parent.saveFile();
            }
            else if(button.getText().equals("Undo")){
                this.parent.statusAppend("\nUndo.");
                this.parent.ctrlZ();
            }
            else if(button.getText().equals("Redo")){
                this.parent.statusAppend("\nRedo.");
                this.parent.ctrlY();
            }
            else if(button.getText().equals("Information")){
                this.parent.statusAppend("\nCheck Software Information.");
                JOptionPane jOptionPane=new JOptionPane();
                jOptionPane.setMessage(Painter.PainterInfo);
                jOptionPane.showMessageDialog(this.parent,String.format("Number: 1813045\n%s\nCollege of Software\n",Painter.PainterInfo),String.format("Information"),JOptionPane.INFORMATION_MESSAGE);
            }
            else if(button.getText().contains("Filling")){
                if(this.parent.drawingBoard.filling){
                    this.parent.fileToolBar.buttonSwitchFilling.setText("Switch: Not Filling");
                    this.parent.drawingBoard.filling=false;
                }
                else{
                    this.parent.fileToolBar.buttonSwitchFilling.setText("Switch: Filling");
                    this.parent.drawingBoard.filling=true;
                }
            }
            else{
                this.parent.statusAppend("\nWrong Operation.");
            }
        }
    }
}

class PaintingToolBar extends JPanel{

    MainWindow parent;

    JButton buttonPen;
    JButton buttonLine;
    JButton buttonRound;
    JButton buttonSquare;
    JButton buttonString;
    JButton buttonFrontColour;
    JButton buttonBackgroundColour;

    PaintingToolBarListener paintingToolBarListener;

    PaintingToolBar(MainWindow parent){
        super(new GridLayout(7,1));
        this.parent=parent;

        this.buttonPen=new JButton("Pen");
        this.buttonLine=new JButton("Line");
        this.buttonRound=new JButton("Round");
        this.buttonSquare=new JButton("Square");
        this.buttonString=new JButton("String");
        this.buttonFrontColour=new JButton("Front Colour");
        this.buttonBackgroundColour=new JButton("Back Colour");

        this.add(this.buttonPen);
        this.add(this.buttonLine);
        this.add(this.buttonRound);
        this.add(this.buttonSquare);
        this.add(this.buttonString);
        this.add(this.buttonFrontColour);
        this.add(this.buttonBackgroundColour);

        this.addListener();
    }
    public void addListener(){
        this.paintingToolBarListener=new PaintingToolBarListener(this.parent);
        this.buttonPen.addActionListener(this.paintingToolBarListener);
        this.buttonLine.addActionListener(this.paintingToolBarListener);
        this.buttonRound.addActionListener(this.paintingToolBarListener);
        this.buttonSquare.addActionListener(this.paintingToolBarListener);
        this.buttonString.addActionListener(this.paintingToolBarListener);
        this.buttonFrontColour.addActionListener(this.paintingToolBarListener);
        this.buttonBackgroundColour.addActionListener(this.paintingToolBarListener);
    }
}
class PaintingToolBarListener implements ActionListener{

    MainWindow parent;

    PaintingToolBarListener(MainWindow parent){
        this.parent=parent;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if(e.getSource().getClass()==JButton.class){
            JButton button=(JButton)e.getSource();
            if(button.getText().equals("Pen")){
                this.parent.statusAppend("\nPen.");
                this.parent.drawingBoard.changeListener(new PenMouseListener(this.parent.drawingBoard),new PenMouseMotionListener(this.parent.drawingBoard));
            }
            else if(button.getText().equals("Line")){
                this.parent.statusAppend("\nLine.");
                this.parent.drawingBoard.changeListener(new LineMouseListener(this.parent.drawingBoard),new LineMouseMotionListener(this.parent.drawingBoard));
            }
            else if(button.getText().equals("Round")){
                this.parent.statusAppend("\nRound.");
                this.parent.drawingBoard.changeListener(new RoundMouseListener(this.parent.drawingBoard),new RoundMouseMotionListener(this.parent.drawingBoard));
            }
            else if(button.getText().equals("Square")){
                this.parent.statusAppend("\nSquare.");
                this.parent.drawingBoard.changeListener(new SquareMouseListener(this.parent.drawingBoard),new SquareMouseMotionListener(this.parent.drawingBoard));
            }
            else if(button.getText().equals("String")){
                this.parent.statusAppend("\nString.");
                this.parent.drawingBoard.changeListener(new StringMouseListener(this.parent.drawingBoard),new StringMouseMotionListener(this.parent.drawingBoard));
            }
            else if(button.getText().equals("Front Colour")){
                this.parent.statusAppend("\nFront Colour.");
                JColorChooser jColorChooser=new JColorChooser();
                Color colour=jColorChooser.showDialog(this.parent,"Choose Front Colour",this.parent.drawingBoard.currentColour);
                if(colour==null){
                    return;
                }
                this.parent.drawingBoard.currentColour=colour;
            }
            else if(button.getText().equals("Back Colour")){
                this.parent.statusAppend("\nBack Colour.");
                JColorChooser jColorChooser=new JColorChooser();
                Color colour=jColorChooser.showDialog(this.parent,"Choose Background Colour",this.parent.drawingBoard.image.backgroundColour);
                if(colour==null){
                    return;
                }
                this.parent.drawingBoard.setBackground(colour);
                this.parent.drawingBoard.image.imageChangeBackgroundColour(colour);
            }
            else{
                return;
            }
        }
    }
}

class MainWindow extends JFrame{

    String softwareName;
    String fileName;
    String filePath;

    FileToolBar fileToolBar;
    DrawingBoard drawingBoard;
    PaintingToolBar paintingToolBar;

    JTextArea status;
    JScrollPane statusScrollPane;

    MainWindow(){
        super();
        this.setTitle("Starting...");
        this.fileToolBar=new FileToolBar(this);
        this.getContentPane().add("North",this.fileToolBar);
        this.drawingBoard=new DrawingBoard(this);
        this.getContentPane().add("Center",this.drawingBoard);
        this.paintingToolBar=new PaintingToolBar(this);
        this.getContentPane().add("West",this.paintingToolBar);

        this.status=new JTextArea(1,1000);
        this.status.setLineWrap(true);
        this.statusScrollPane=new JScrollPane(this.status);
        this.getContentPane().add("South",this.statusScrollPane);

        this.setMinimumSize(new Dimension(800,600));
        this.setMaximumSize(new Dimension(4096,2160));
        this.setSize(1080,720);

        this.enableEvents(AWTEvent.WINDOW_EVENT_MASK);
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setVisible(true);
    }
    MainWindow(String SoftwareName){
        this();
        this.softwareName=SoftwareName;
        this.fileName="Untitled";
        this.filePath="Untitled";
        this.setTitle(String.format("%s  -  %s",this.fileName,this.softwareName));
    }
    MainWindow(String FilePath,String SoftwareName){
        this();
        this.softwareName=SoftwareName;
        this.filePath=FilePath;
        this.fileName=dealName();
        this.openFile(FilePath);
        this.setTitle(String.format("%s  -  %s",this.fileName,this.softwareName));
    }
    protected String dealName(){
        if(this.filePath.contains("/")){
            return this.filePath.substring(this.filePath.lastIndexOf('/')+1);
        }
        else{
            return this.filePath;
        }
    }
    protected void createFile(String Name){
        this.fileName=Name;
        this.filePath=Name;
        this.setTitle(String.format("%s  -  %s",this.fileName,this.softwareName));
    }
    protected void openFile(String path){
        this.filePath=path;
        this.fileName=this.dealName();
        Image temp=new Image();
        try{
            FileInputStream fileInputStream=new FileInputStream(path);
            BufferedInputStream bufferedInputStream=new BufferedInputStream(fileInputStream);
            ObjectInputStream objectInputStream=new ObjectInputStream(bufferedInputStream);

            temp=(Image)objectInputStream.readObject();

            objectInputStream.close();
            bufferedInputStream.close();
            fileInputStream.close();
        }
        catch(Exception e){
            e.printStackTrace();
        }
        this.drawingBoard.changeImage(temp);
        this.setTitle(String.format("%s  -  %s",this.fileName,this.softwareName));
    }
    protected void saveFile(){
        try {
            this.drawingBoard.saveImage();
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
    public void statusAppend(String message){
        this.status.append(message);
    }
    public void ctrlZ(){
        this.drawingBoard.ctrlZ();
    }
    public void ctrlY(){
        this.drawingBoard.ctrlY();
    }

    @Override
    protected void processWindowEvent(WindowEvent e){
        if (e.getID() == WindowEvent.WINDOW_CLOSING) {
            if(!this.drawingBoard.edit){
                super.processWindowEvent(e);
                return;
            }
            JOptionPane jOptionPane = new JOptionPane();
            int result = jOptionPane.showConfirmDialog(this, "Save current file before close?", "Are you sure to close?", JOptionPane.YES_NO_CANCEL_OPTION);
            switch (result) {
                case 0:
                    this.saveFile();
                    super.processWindowEvent(e);
                case 1:
                    super.processWindowEvent(e);
                case 2:
                    return;
                default:
                    return;
            }
        }
        super.processWindowEvent(e);
    }
    // Prompt whether save current file before exit.
}

public class Painter{
    public static String PainterInfo="Painter - 1.0.";
    private String softwareName;
    private String version;
    Painter(){
        this.softwareName="Painter";
        this.version="1.0";
    }
    public static void main(String []args){
        Painter painter=new Painter();
        painter.run(); // Default Run with Untitled Empty File.
    }
    public void run(){
        MainWindow painter=new MainWindow(this.softwareName);
    }
    public void run(String filePath){
        MainWindow filePainter=new MainWindow(filePath,this.softwareName);
    }
    public String getInfo(){
        return String.format("%s %s.",this.softwareName,this.version);
    }
}
