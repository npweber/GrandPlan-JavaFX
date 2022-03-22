package nathan.apes.grandplan.month;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import nathan.apes.grandplan.Main;
import nathan.apes.grandplan.mainwin.MainWindow;

public class MonthPicker {

    private Main main = new Main();

    private final Stage stage;

    public MonthPicker(){
        this.stage = new Stage();
        stage.setTitle("Select Month");
        stage.setScene(new Scene(this.buildUI(), 270.0, 420.0));
        stage.show();
    }

    private VBox buildUI(){
        VBox ui = new VBox();

        ImageView header = new ImageView(new Image(getClass().getResourceAsStream("monthPicker.jpg")));

        GridPane months = new GridPane();
        int row = 0;
        for(int i = 1; i <= 12; i++) {
            int collum = 0;
            if(i % 2 == 0)
                collum = 1;
            else
                row++;
            if(i == 1)
                row = 0;
            Button monthPicker = new Button("", new ImageView(new Image(getClass().getResourceAsStream("month/" + String.valueOf(i) + ".jpg"))));
            final int monthSelected = i;
            monthPicker.setOnAction(action -> {
                stage.close();
                MainWindow.stage.close();
                new MainWindow(main.cppBridge().fabricateStamp(monthSelected, 1));
            });
            months.add(monthPicker, collum, row);
        }

        ui.getChildren().addAll(header, months);
        return ui;
    }
}
