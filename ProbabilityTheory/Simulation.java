import java.util.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.*;

public class Simulation{
	public static void main(String []args) {
		Simulation simulation = new Simulation();
//		simulation.init(100, 100, 100);
		// DataSet.
		try {
			boolean created = false;
			File dataSetDirectory = new File("dataSet");
			if(dataSetDirectory.exists()) {
				Scanner choosingNewOrExistScanner = new Scanner(System.in);
				System.out.println("Here exists a dataSet, whether create a new one? (Yes/No).");
				String choosing = choosingNewOrExistScanner.nextLine();
				if(choosing.contentEquals("No")||choosing.contentEquals("N")) {
					// Use old dataSet.
					// Get the dataSetSize.
					File list[] = dataSetDirectory.listFiles();
					int counter = 0;
					for(int cursor = 0; cursor < list.length; cursor++) {
						if(list[cursor].isFile()) {
							counter++;
						}
					}
					simulation.setSize(counter);
					// Get the dataSize.
					File zeroFile = new File("dataSet\\0.txt");
					if(zeroFile.exists()) {
						FileReader fileReader = new FileReader(zeroFile);
						BufferedReader bufferedReader = new BufferedReader(fileReader);
						int row=0;
						while((bufferedReader.readLine()) != null){
							row++;
						}
						bufferedReader.close();
						fileReader.close();
						System.out.println(String.format("The dataSet have %d files, %d rows per file.", counter, row));
						simulation.setDataSize(row);
						created = true;
						// Choosing type.
						System.out.println("Please input type: '1: Random', '2: Method', '3: Group'.");
						String typeString = choosingNewOrExistScanner.nextLine();
						choosingNewOrExistScanner.close();
						int type = Integer.parseInt(typeString);
						simulation.setType(type);
					} else {
						System.out.println("The dataSet is wrong, it will create a new one.");
						deleteFileOfDirectory(dataSetDirectory);
					}
				} else {
					deleteFileOfDirectory(dataSetDirectory);
//					dataSetDirectory.mkdir();
				}
			} else {
				// Here not exists 'dataSet' directory.
//				dataSetDirectory.mkdir();
			}
			if(!created) {
				// Create directory and create new dataSet.
				dataSetDirectory.mkdir();
				System.out.println("Please input dataSetSize dataSize and Type like '100 100 1', 100 < number < 1000, '1: Random', '2: Method', '3: Group'.");
				Scanner inputScanner = new Scanner(System.in);
				String argsInput = inputScanner.nextLine();
				String[] argsList = argsInput.split(" ");
				simulation.init(Integer.parseInt(argsList[0]), Integer.parseInt(argsList[1]), Integer.parseInt(argsList[2]));
			}
			Thread.sleep(1000);
		} catch (Exception ex) {
			ex.printStackTrace();
		}
		try {
			simulation.start();
			try {
				simulation.writeFile();
				System.out.println("The result has saved at 'Result\\report.txt'.");
			} catch (IOException ioException) {
				ioException.printStackTrace();
				System.out.println("Can not save the result.");
				simulation.printResult();
			}
		} catch (IOException ie) {
			ie.printStackTrace();
			File dataSetDirectory = new File("dataSet");
			if(dataSetDirectory.exists()) {
				deleteFileOfDirectory(dataSetDirectory);
			}
			System.out.println("Crashed files have been deleted. Please run it again.");
		}
	}
	
	public static void deleteFileOfDirectory(File fileDirectory) {
		if (fileDirectory == null || !fileDirectory.exists()){
            System.out.println("Wrong FileDirectory.");
            return;
        }
        File[] files = fileDirectory.listFiles();
        for (File f: files){
            String name = f.getName();
            System.out.println(String.format("Delete %s", name));
            if (f.isDirectory()){
                deleteFileOfDirectory(f);
            } else {
                f.delete();
            }
        }
        fileDirectory.delete();
	}
	
	private class DataCreater implements Runnable {

		int size;
		String name;
		
		@Override
		public void run() {
			// TODO Auto-generated method stub
//			ArrayList drawerArrayList = new ArrayList();
			ArrayList numberArrayList = new ArrayList();
			Random random = new Random();
			for(int cursor = this.size - 1; cursor >= 0; cursor--) {
//				drawerArrayList.add(cursor); // Auto boxing.
//				numberArrayList.add(this.size - cursor - 1); // Reverse input.
				numberArrayList.add(cursor); // Auto boxing reverse input.
			}
				
		    for(int exchange = 0; exchange < this.size; exchange++) {
		    	double rate = random.nextDouble();
		    	while(rate == 1.0) {
		    		rate = random.nextDouble();
		    	}
		    	int current = (int)numberArrayList.get(exchange);
		    	numberArrayList.set(exchange, numberArrayList.get((int)(rate*this.size)));
		    	numberArrayList.set((int)(rate*this.size), current);
		    }
		    
//		    File dataSet = new File(String.format("C:\\dataSet\\%s.txt", this.name));
		    File dataSet = new File(String.format("dataSet\\%s.txt", this.name));
		    try {
		    	FileWriter fileWriter = new FileWriter(dataSet);
		    	for(int fileCursor = 0; fileCursor < this.size; fileCursor++) {
		    		fileWriter.write(String.format("%d\n", (int)numberArrayList.get(fileCursor)));
		    	}
		    	fileWriter.close();
	        
		    } catch (IOException e) {
		    	// TODO Auto-generated catch block
		    	e.printStackTrace();
		    }
		}
		
		public void setName(int index) {
			this.name = Integer.toString(index, 10);
		}
		
		public void setSize(int size) {
			this.size = size;
		}
		
	}
	
	private class SimulationLab extends Thread {

		int type;
		ArrayList drawer;
		ArrayList number;
		
		public SimulationLab() {
			// TODO Auto-generated constructor stub
			this.drawer = new ArrayList();
			this.number = new ArrayList();
		}
		
		@Override
		public void run() {
			int result;
			result = 0;
			addResult(result);
			switch(this.type) {
				case 1:
					this.random();
					break;
				case 2:
					this.method();
					break;
				case 3:
					this.group();
					break;
				default:
					break;
			}
		}

		public void readNumber(int index, int rows) throws IOException {
			File number = new File(String.format("dataSet\\%d.txt", index));
			if(number.exists()) {
				FileReader fileReader = new FileReader(number);
				BufferedReader bufferedReader = new BufferedReader(fileReader);
				String line;
				int row=0;
				while((line = bufferedReader.readLine()) != null){
					this.number.add(Integer.parseInt(line));
					row++;
				}
				if(row != rows) {
					throw new IOException("File crashed.");
				}
				bufferedReader.close();
				fileReader.close();
			} else {
				throw new IOException("File not found.");
			}
		}

		public void setType(int type) {
			this.type = type;
		}

		public void random() {

		}

		public void method() {

		}

		public void group() {

		}
	}
	
	private int size;
	private int dataSize;
	private int type;
	private ArrayList labsArrayList;
	volatile private ArrayList dataArrayList;
	File result;
	
	private void init(int size, int dataSize, int type) {
		this.size = size;
		this.dataSize = dataSize;
		this.type = type;
		this.labsArrayList = new ArrayList();
		this.dataArrayList = new ArrayList();
		for(int cursor = 0; cursor < size; cursor++) {
			DataCreater dataCreater = new DataCreater();
			dataCreater.setSize(size);
			dataCreater.setName(cursor);
			dataCreater.run();
		}
	}
	
	private void setSize(int size) {
		this.size = size;
	}
	
	private void setDataSize(int dataSize) {
		this.dataSize = dataSize;
	}
	
	private void setType(int type) {
		this.type = type;
	}

	private int getSize() {
		return this.size;
	}

	private int getDataSize() {
		return this.dataSize;
	}

	private int getType() {
		return this.type;
	}

	private void randomLab() {

	}

	private void methodLab() {

	}

	private void groupLab() {

	}

	private void start() throws IOException{

		for(int cursor = 0; cursor < this.size; cursor++) {
			SimulationLab simulationLab = new SimulationLab();
			simulationLab.setType(this.getType());
			simulationLab.readNumber(cursor, this.dataSize);
			this.labsArrayList.add(simulationLab);
		}

		switch(this.type) {
			case 1:
				this.randomLab();
				break;
			case 2:
				this.methodLab();
				break;
			case 3:
				this.groupLab();
				break;
			default:
				System.out.println("Wrong Method.");
				break;
		}
	}

	private void addResult(int result) {
		this.dataArrayList.add(result);
	}

	private void writeFile() throws IOException {
		this.result = new File("Result");
		if(!this.result.exists()) {
			this.result.mkdir();
		}
		this.result = new File("Result\\report.txt");
		if(!this.result.exists()) {
			this.result.createNewFile();
		}
	}

	private void printResult() {

	}
}
