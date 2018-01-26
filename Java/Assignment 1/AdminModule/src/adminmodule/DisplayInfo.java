package adminmodule;

import java.util.*; 
import java.io.*; 

public class DisplayInfo {
    public static void lookPlayerInfo () 
        {
        System.out.println ("\nOption 5: Displaying player info\n");
        
        try 
                {
                    printPlayerInfo ("players.dat");        
                }
            
            catch (FileNotFoundException ex)
                {
                   System.out.print ("File players.dat cannot be found. Please create the file using Option 2. Create a player\n");
                }
            
            catch (IOException error)
                {
                    System.out.print ("Error in displaying player info, please ensure that there is no folder or file named players.dat\n");
                } 
    }
    public static void printPlayerInfo (String args) throws IOException 
    {
        Scanner input = new Scanner (System.in);
        
        boolean found = false;  
        String playerName;
        
        String name = " "; 
        
        Scanner fileInput;
        fileInput = new Scanner (new File (args)); 
        
        System.out.print ("Please enter the name of the player you wish to display: ");
        name = input.nextLine();
        
        String temp;
        String [] dummy = new String [50]; 

        
       while (fileInput.hasNextLine())
        {
            temp = fileInput.nextLine ();
            
            dummy = temp.split ("\\|");
            playerName = dummy[0];
            
            if (name.equalsIgnoreCase(playerName))
            {
                System.out.println (temp+ "\n");
                found = true; 
            }
            
        } 
        
        fileInput.close (); 
        
        if (found == false)
        {
             System.out.println ("Sorry, the player you are looking for is not available");
        }
        
    }
}
