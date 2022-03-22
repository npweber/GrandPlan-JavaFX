package nathan.apes.grandplan;

import javafx.application.Application;
import javafx.stage.Stage;

import cpb.CPPBridge;

import nathan.apes.grandplan.mainwin.MainWindow;

public class Main extends Application {

    private final CPPBridge cppBridge = new CPPBridge();

    @Override
    public void start(Stage primaryStage) throws Exception{
         new MainWindow(cppBridge.currentDate());
    }

    public static void main(String[] args) {
        launch(args);
    }

    public CPPBridge cppBridge(){
        return cppBridge;
    }
}
