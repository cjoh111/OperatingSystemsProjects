import java.net.*;
import java.io.*;
public class NameClient {
    public static void main(String[] args){
        try {
            Socket clientSocket = new Socket("profeckert.com", 3501);
            System.out.println("ACO350 NameClient - Cole Johnson");
            PrintWriter id = new PrintWriter(clientSocket.getOutputStream(), true);
            id.println("ID:1224997215");
            InputStream message = clientSocket.getInputStream();
            BufferedReader bin = new BufferedReader(new InputStreamReader(message));

            String response;
            while((response = bin.readLine()) != null) {
                System.out.printf("Client heard: \"%s\"", response);
            }

            clientSocket.close();
        }
        catch (IOException ioe) {
            System.err.println(ioe);
        }
    }
}
