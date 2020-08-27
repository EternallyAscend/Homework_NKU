import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.URL;

import java.net.*;
import java.io.*;
import java.util.Scanner;

public class Web {
    public static void main(String []args){
        int no1 = 0;
        try {
            if (no1 == 0) throw new Exception("");
            URL web = new URL("https://www.nankai.edu.cn");
            System.out.println(web.getProtocol());
            System.out.println(web.getHost());
            System.out.println(web.getPort());
            System.out.println(web.getFile());
            BufferedReader in = new BufferedReader(new InputStreamReader(web.openStream()));
            String inputLine;
            //while ((inputLine = in.readLine()) != null) System.out.println(inputLine);
            in.close();
            URLConnection urlConnection = web.openConnection();
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(urlConnection.getInputStream()));
            while ((inputLine = bufferedReader.readLine()) != null) {
//                System.out.println(inputLine);
            }
            bufferedReader.close();
        }
        catch (Exception e) {
            // This is try to read web file lines.
            // Two methods are the same result.
        }
        try {
            if (no1 == 0) throw new Exception("");
            InetAddress inetAddress = InetAddress.getLocalHost();
            System.out.println(inetAddress);
            byte[] address = inetAddress.getAddress();
            for (int i = 0; i < address.length ; i++) {
                System.out.println(address[i]);
            }
            System.out.println(inetAddress.getHostName());
            System.out.println(inetAddress.getHostAddress());
        }
        catch (Exception e) {

        }
        try {
            URL url = new URL("https://www.baidu.com/");
            System.out.println(url);
            URL baseUrl = new URL(url,"file.html");
            System.out.println(baseUrl);

            URL socketUrl = new URL("https://101.200.100.121:8080");
            System.out.println(socketUrl);
            System.out.println(socketUrl.getProtocol());
            System.out.println(socketUrl.getHost());
            System.out.println(socketUrl.getPort());
            System.out.println(socketUrl.getFile());
            System.out.println(socketUrl.getRef());
        }
        catch (MalformedURLException e) {

        }
        try {
            System.out.println("First");
//            Socket socket = new Socket("101.200.155.187",8080);

            System.out.println("Local Host");
            ServerSocket serverSocket = new ServerSocket(8080);
            System.out.println(serverSocket);
            System.out.println(serverSocket.getLocalSocketAddress());
            System.out.println(serverSocket.getLocalPort());
            serverSocket.close();
        }
        catch (Exception e) {

        }
    }
}



class TestUrl {
    public static void main(String[] args) throws Exception {
        URL web = new
                URL("http://www.nankai.edu.cn");
        System.out.println(web.getProtocol());
        System.out.println(web.getHost());
        System.out.println(web.getPort());
        System.out.println(web.getFile());
        BufferedReader in = new BufferedReader(
                new InputStreamReader(web.openStream()));
                String inputLine;
                while ((inputLine = in.readLine()) != null)
                    System.out.println(inputLine);
                in.close();
    }
}