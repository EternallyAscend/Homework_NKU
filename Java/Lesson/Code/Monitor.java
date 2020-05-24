// package OnlineJudge;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.util.Date;
import java.util.HashMap;

class FileMonitor{
    volatile boolean running;
    String monitorPath;
    String logPath;
    Path path;
    File record;
    FileWriter fileWriter;

    HashMap<WatchKey,Path> hashMap;

    WatchService watchService;

    FileMonitor(String MonitorPath){
        this.monitorPath=MonitorPath;
        this.logPath="Monitor.txt";
        this.record=new File(this.logPath);
        this.createMonitor();
    }
    FileMonitor(String MonitorPath,String logPath){
        this.monitorPath=MonitorPath;
        this.logPath=logPath;
        this.record=new File(this.logPath);
        this.createMonitor();
    }

    protected void createMonitor(){
        this.hashMap=new HashMap<WatchKey,Path>();
        try{
            this.watchService=FileSystems.getDefault().newWatchService();
            this.path=Paths.get(this.monitorPath);
            registerTree(this.path);
        }
        catch(Exception e){

        }
    }
    protected void registerPath(Path registerPath) throws IOException{
        WatchKey watchKey=registerPath.register(this.watchService,StandardWatchEventKinds.ENTRY_CREATE,StandardWatchEventKinds.ENTRY_DELETE,StandardWatchEventKinds.ENTRY_MODIFY);
        this.hashMap.put(watchKey,registerPath);
    }
    protected void registerTree(Path rootPath) throws IOException{
        Files.walkFileTree(rootPath,new SimpleFileVisitor<Path>(){
                    @Override
                    public FileVisitResult preVisitDirectory(Path dir, BasicFileAttributes attrs) throws IOException {
                        registerPath(dir);
                        return FileVisitResult.CONTINUE;
                    }
                }
        );
    }
    protected void record(String message) throws IOException{
        this.fileWriter=new FileWriter(this.record,true);
        this.fileWriter.append(message+System.getProperty("line.separator"));
        this.fileWriter.close();
    }
    public void startMonitor() throws IOException, InterruptedException {
        this.running=true;
        while(this.running){
            final WatchKey key = watchService.take();
            for (WatchEvent<?> watchEvent : key.pollEvents()) {
                final WatchEvent.Kind<?> kind = watchEvent.kind();
                final WatchEvent<Path> watchEventPath = (WatchEvent<Path>) watchEvent;
                final Path filename = watchEventPath.context();
                if (kind==StandardWatchEventKinds.OVERFLOW) {
                    continue;
                }
                if (kind==StandardWatchEventKinds.ENTRY_CREATE) {
                    final Path directory_path = this.hashMap.get(key);
                    final Path child = directory_path.resolve(filename);
                    if (Files.isDirectory(child, LinkOption.NOFOLLOW_LINKS)) {
                        this.registerTree(child);
                    }
                }
                this.record(String.format("%s %s %s",String.valueOf(new Date()),String.valueOf(kind),filename));
            }
            boolean valid=key.reset();
            if (!valid) {
                this.hashMap.remove(key);
                if (this.hashMap.isEmpty()) {
                    break;
                }
            }
        }
    }
    public void stopMonitor(){
        this.running=false;
    }
}

public class Monitor {
    public static void main(String []args){
        try {
            FileMonitor fileMonitor=new FileMonitor("D:/Java-Project");
//            FileMonitor fileMonitor=new FileMonitor("D:/Program Files");
            fileMonitor.startMonitor();
        }
        catch(Exception e){
            e.printStackTrace();
        }
    }
}
