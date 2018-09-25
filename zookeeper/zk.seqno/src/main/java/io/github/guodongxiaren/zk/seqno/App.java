package io.github.guodongxiaren.zk.seqno;

public class App extends Thread {
	private long timeStart;
	private int seqNoStart;

	public App(long timeStart, int seqNoStart) {
		super();
		this.timeStart = timeStart;
		this.seqNoStart = seqNoStart;
	}

	public static void main(String[] args) throws Exception {
		try {
			// SeqNo.regAppId("userid");
		} catch (Exception e) {
			e.printStackTrace();
		}
		Thread[] ts = new App[500];
		int seqNo = SeqNo.get("userid");
		long timeStart = System.currentTimeMillis();

		for (Thread t : ts) {
			t = new App(timeStart, seqNo);
			t.start();
			try {
				t.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}

	}

	@Override
	public void run() {
		super.run();
		try {
			int seqNo = SeqNo.get("userid");
			long timeEnd = System.currentTimeMillis();
			System.out.println("time:" + (timeEnd - timeStart) + "|" + (seqNo - seqNoStart));
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
