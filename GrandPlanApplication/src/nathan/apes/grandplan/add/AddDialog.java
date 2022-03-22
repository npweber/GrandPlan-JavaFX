package nathan.apes.grandplan.add;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import nathan.apes.grandplan.Main;
import nathan.apes.grandplan.daywin.DayEditor;
import nathan.apes.grandplan.mainwin.MainWindow;

public class AddDialog {

    private Main main = new Main();

    private final int dayIndex;

    private final Stage addDialog;

    public AddDialog(int dayIndex){
        this.dayIndex = dayIndex;

        this.addDialog = new Stage();
        addDialog.setTitle("Add Event");
        addDialog.setScene(new Scene(this.buildUI(), 300.0, 50.0));
        addDialog.show();
    }

    private VBox buildUI() {
        VBox ui = new VBox();

        HBox fields = new HBox();
        Text hourPrompt = new Text("Time: ");
        TextField hourField = new TextField();
        Text titlePrompt = new Text("Title: ");
        TextField titleField = new TextField();
        Text descPrompt = new Text("Description: ");
        TextField descField = new TextField();
        fields.getChildren().addAll(hourPrompt, hourField, titlePrompt, titleField, descPrompt, descField);

        Button submitButton = new Button("Add");
        submitButton.setOnAction(action -> {
            if (hourField.getText().length() > 0 && titleField.getText().length() > 0 && descField.getText().length() > 0) {
                String hourString = hourField.getText().substring(0, 2);
                if(hourString.contains("A") || hourString.contains("P"))
                    hourString = hourString.substring(0, 1);
                if(main.cppBridge().titles(Integer.parseInt(hourString) + (dayIndex * 24)).length() < 1) {
                    int hour = Integer.parseInt(hourString);
                    if(hourField.getText().contains("PM") && (!hourField.getText().equalsIgnoreCase("12PM")))
                        hour += 12;
                    main.cppBridge().encodeEvent(hour + (dayIndex * 24), titleField.getText(), descField.getText());
                    addDialog.close();
                    MainWindow.stage.close();
                    new MainWindow(MainWindow.getDateStamp());
                    DayEditor.stage.close();
                    new DayEditor(dayIndex);
                }
            }
        });

        ui.getChildren().addAll(fields, submitButton);

        return ui;
    }
}
