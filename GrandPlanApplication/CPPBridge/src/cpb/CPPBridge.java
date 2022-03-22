package cpb;

public class CPPBridge {
	
	public CPPBridge(){
		System.load(System.getProperty("user.dir") + "/lib/GrandPlanAPI.dll");
	}

    public native void dataRetrieval(String dateStamp);

	public native void encodeEvent(int inputIndex, String title, String description);

	public native void removeEvent(int indexInput);

	public native String titles(int index);

    public native String descriptions(int index);

	public native String currentDate();

	public native String weekStartOffset(String inputDay, String inputMonth);

	public native String fabricateStamp(int month, int numWeek);
}
