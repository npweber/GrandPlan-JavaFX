package nathan.apes.grandplan.mainwin;

import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.image.*;
import javafx.scene.layout.*;

import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.scene.text.TextAlignment;
import javafx.stage.Stage;
import nathan.apes.grandplan.Main;
import nathan.apes.grandplan.daywin.DayEditor;
import nathan.apes.grandplan.month.MonthPicker;

public class MainWindow {

    private final Main main = new Main();

    public static Stage stage;

    private static String dateStamp;

    public MainWindow(String input){
        dateStamp = input;

        stage = new Stage();
        stage.setTitle("GrandPlan");
        stage.setScene(new Scene(this.buildUI(), 310, 450));
        stage.show();
    }

    public VBox buildUI(){
        VBox ui = new VBox();

        ImageView editHeader = new ImageView(new Image(getClass().getResourceAsStream("editor.jpg")));
        ImageView monthImage = new ImageView(new Image(getClass().getResourceAsStream("monthButton.jpg")));
        ImageView week = new ImageView(new Image(getClass().getResourceAsStream("week.jpg")));
        ImageView weekdays = new ImageView(new Image(getClass().getResourceAsStream("weekDisplay.jpg")));

        HBox header = new HBox();
        String month = dateStamp.substring(dateStamp.indexOf("M:") + 2, dateStamp.indexOf("M:") + 4);
        String day = dateStamp.substring(dateStamp.indexOf("D:") + 2, dateStamp.indexOf("D:") + 4);
        String date = "\n" + month + "/" + day + "/2018";
        Text dateImage = new Text(date);
        dateImage.setFont(new Font(16.0));
        dateImage.setTextAlignment(TextAlignment.CENTER);
        header.getChildren().addAll(editHeader, dateImage);

        HBox dateSelect = new HBox();
        GridPane weekBox = new GridPane();
        int row = 0;
        final int currentMonth = Integer.parseInt(dateStamp.substring(dateStamp.indexOf("/") + 1, dateStamp.indexOf("/") + 3));
        for(int i = 1; i <= 4; i++){
            int collum = 0;
            if(i % 2 == 0)
                collum = 1;
            else
                row++;
            if(i == 1)
                row = 0;
            Button selectWeek = new Button("", new ImageView(new Image(getClass().getResourceAsStream("week/week" + i + ".jpg"))));
            final int weekSelected = i;
            selectWeek.setOnAction(action -> {
                stage.close();
                new MainWindow(main.cppBridge().fabricateStamp(currentMonth, weekSelected));
            });
            weekBox.add(selectWeek, collum, row);
        }
        String week5Image = "week5NA.jpg";
        String week5Id = "NA";
        if(currentMonth == 3 || currentMonth == 6 || currentMonth == 8 || currentMonth == 11) {
            week5Image = week5Image.replace("NA", "");
            week5Id = "GO";
        }
        Button week5Button = new Button("", new ImageView(new Image(getClass().getResourceAsStream("week/" + week5Image))));
        week5Button.setId(week5Id);
        if(week5Button.getId().equals("GO"))
            week5Button.setOnAction(action -> {
                stage.close();
                new MainWindow(main.cppBridge().fabricateStamp(currentMonth, 5));
            });
        week5Button.setTranslateY(20.0);

        Button monthButton = new Button("", monthImage);
        monthButton.setOnAction(action -> new MonthPicker());
        monthButton.setScaleX(0.9);
        monthButton.setTranslateX(-10.0);
        dateSelect.getChildren().addAll(week, weekBox, week5Button, monthButton);

        HBox weekLayout = new HBox();
        VBox daysDisplay = new VBox();
        daysDisplay.getChildren().add(weekdays);
        VBox datesDisplay = new VBox();
        datesDisplay.setSpacing(30.0);
        VBox editDays = new VBox();
        editDays.setSpacing(20.0);
        GridPane daysView = new GridPane();
        main.cppBridge().dataRetrieval(dateStamp);
        int[] monthDays = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        for(int i = 0; i < 7; i++) {
            int numDay = (Integer.parseInt(day) - Integer.parseInt(main.cppBridge().weekStartOffset(day, month))) + i;
            int numMonth = Integer.parseInt(month);
            int factor = 1;
            if(numDay <= 0) {
                numDay = monthDays[numMonth - 2] + numDay;
                numMonth--;
                factor +=2;
            }
            final int prevMonthAmount;
            if(numDay > monthDays[numMonth - factor]) {
                prevMonthAmount = monthDays[numMonth - 1];
                numDay -= prevMonthAmount;
                numMonth++;
            }
            String localDay = String.valueOf(numDay);
            if(localDay.length() <= 1)
                localDay = "0".concat(localDay);
            String localMonth = String.valueOf(numMonth);
            if(localMonth.length() <= 1)
                localMonth = "0".concat(localMonth);
            Text dateDisplay = new Text(localMonth + "/" + localDay);
            datesDisplay.getChildren().add(dateDisplay);
            Button editDay = new Button("Edit");
            editDay.setTranslateX(1.0);
            final int dayIndex = i;
            editDay.setOnAction(action -> new DayEditor(dayIndex));
            editDays.getChildren().add(editDay);
            for (int j = 9; j < 17; j++) {
                int hour = j;
                if (hour > 12)
                    hour -= 12;
                String eventTitle = String.valueOf(hour) + " \n";
                if (main.cppBridge().titles(j + (i * 24)).length() >= 3)
                    eventTitle = eventTitle.concat(main.cppBridge().titles(j + (i * 24)).substring(0, 3));
                else if(main.cppBridge().titles(j + (i * 24)).length() > 0 && main.cppBridge().titles(j + (i * 24)).length() < 3)
                    eventTitle = eventTitle.concat("<>");
                Text event = new Text(eventTitle);
                event.setFont(new Font(16.0));
                daysView.add(event, j, i);
            }
        }
        weekLayout.getChildren().addAll(datesDisplay, editDays, daysDisplay, daysView);

        ui.getChildren().addAll(header, dateSelect, weekLayout);

        return ui;
    }

    public static String getDateStamp() {
        return dateStamp;
    }
}
