package io.github.guodongxiaren.zk.seqno;

import java.util.concurrent.CountDownLatch;

import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.Watcher.Event.KeeperState;
import org.apache.zookeeper.ZooDefs;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;

public class SeqNo {
	private static ZooKeeper zk;
	private static final Object lock = new Object();

	private static ZooKeeper getZooKeeper() throws Exception {

		if (zk == null) {
			synchronized (lock) {
				zk = (zk == null) ? new ZooKeeper("127.0.0.1:2181", 500000, null) : zk;
			}

			// connectedSemaphore.await();
		}
		return zk;
	}

	/**
	 * 注册新的APPID对应的Znode 业务方自己保重APPID唯一
	 * 
	 * @param appId
	 * @throws Exception
	 */
	public static void regAppId(String appId) throws Exception {
		ZooKeeper zk = getZooKeeper();

		System.out.println(zk.getChildren("/", null));
		if (zk.exists("/appid", null) == null) {
			zk.create("/appid", "111".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
		}
		String path = getAppIdPath(appId);
		zk.create(path, "".getBytes(), ZooDefs.Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
	}

	/**
	 * 获得新的全局地址序列号
	 * 
	 * @param appId
	 * @return
	 * @throws Exception
	 */
	public static int get(String appId) throws Exception {
		String path = getAppIdPath(appId);
		Stat stat = getZooKeeper().setData(path, "".getBytes(), -1);
		return stat.getVersion();

	}

	/**
	 * 通过APPID获得Znode路径
	 * 
	 * @param appId
	 * @return
	 */
	private static String getAppIdPath(String appId) {
		return String.format("/appid/%s", appId);
	}

}
