package net.infinite_labs.platform_core;

public class TestRunner {
	static {
		System.loadLibrary("PlatformCore-Android-Tests");
	}
	
	public static class Outcome {
		private String testCase;
		private String description;
		private boolean passed;

		public String getTestCase() {
			return testCase;
		}
		public String getDescription() {
			return description;
		}
		public boolean isPassed() {
			return passed;
		}

		public Outcome(String testCase, String description, boolean passed) {
			super();
			this.testCase = testCase;
			this.description = description;
			this.passed = passed;
		}
		
		public String toString() {
			return (isPassed()? "\u2713" : "\u2717") + " " + description;
		}
	}
	
	public interface ResultsReceiver {
		void testPerformed(Outcome o);
	}
	
	private ResultsReceiver receiver;
	
	protected native void nativeRunTests();

	private String currentTestCaseName;
	
	public void didBeginTestCase(String testCaseName, String testName) {
		currentTestCaseName = testCaseName + " (" + testName + ")";
	}
	
	public void passed(String description) {
		if (receiver != null)
			receiver.testPerformed(new Outcome(currentTestCaseName, description, true));
	}
	
	public void failed(String description) {
		if (receiver != null)
			receiver.testPerformed(new Outcome(currentTestCaseName, description, true));		
	}
	
	public TestRunner(ResultsReceiver r) {
		receiver = r;
	}
	
	public void run() {
		nativeRunTests();
	}
}
