package nathan.apes.grandplan.daywin;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import nathan.apes.grandplan.Main;
import nathan.apes.grandplan.add.AddDialog;
import nathan.apes.grandplan.mainwin.MainWindow;

public class DayEditor {

    private final Main main = new Main();

    private final int dayIndex;

    public static Stage stage;

    public DayEditor(int index){
        this.dayIndex = index;

        stage = new Stage();
        stage.setTitle("Day Editor");
        stage.setScene(new Scene(this.buildUI(), 290.0, 450.0));
        stage.setScene(new Scene(this.buildUI(), 290.0, 450.0));
        stage.show();
    }

    private VBox buildUI(){
        VBox ui = new VBox();

        HBox header = new HBox();
        ImageView dayHeader = new ImageView(new Image(getClass().getResourceAsStream("dayEditor.jpg")));
        Button addButton = new Button("", new ImageView(new Image(getClass().getResourceAsStream("addButton.jpg"))));
        addButton.setOnAction(action -> new AddDialog(dayIndex));
        header.getChildren().addAll(dayHeader, addButton);

        String[] titles = new String[24];
        String[] descriptions = new String[24];
        ScrollPane contents = new ScrollPane();
        GridPane day = new GridPane();
        for(int i = 0; i < 24; i++){
            if(main.cppBridge().titles((dayIndex * 24) + i).length() > 0) {
                Button remove = new Button("Remove");
                final int hour = i;
                remove.setOnAction(action -> {
                    main.cppBridge().removeEvent((dayIndex * 24) + hour);
                    MainWindow.stage.close();
                    new MainWindow(MainWindow.getDateStamp());
                    DayEditor.stage.close();
                    new DayEditor(dayIndex);
                });
                day.add(remove, 0, i);
            }
            String imageName = "time/";
            if(i == 0){
                imageName = imageName.concat("12AM.jpg");
                continue;
            }
            if(i == 12) {
                imageName = imageName.concat("12PM.jpg");
                continue;
            }
            if(i < 12)
                imageName = imageName.concat(String.valueOf(i) + "AM.jpg");
            else
                imageName = imageName.concat(String.valueOf(i - 12) + "PM.jpg");
            day.add(new ImageView(new Image(getClass().getResourceAsStream(imageName))), 1, i);

            titles[i] = main.cppBridge().titles((dayIndex * 24) + i);
            descriptions[i] = main.cppBridge().descriptions((dayIndex * 24) + i);
            if(titles[i].length() > 0)
                day.add(new Text("Test"), 2, i);
        }
        contents.setContent(day);

        ui.getChildren().addAll(header, contents);
        return ui;
    }
}
