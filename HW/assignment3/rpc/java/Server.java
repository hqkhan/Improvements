import org.apache.xmlrpc.*;
import java.util.*;

public class Server { 

   public Vector add(int x, int y){
      Vector returnValue = new Vector();
      returnValue.addElement(new Integer(7));
      returnValue.addElement(new Double(2.78));
      returnValue.addElement(new String("hello world"));
	System.out.println("calling add");
      return returnValue;
   }

   public static void main (String [] args){
   
      try {
         WebServer server = new WebServer(8080);
         server.addHandler("sample", new Server());
         server.start();
      } catch (Exception exception){
         System.err.println("JavaServer: " + exception);
      }
   }
}
