package adminmodule;

import java.util.*; 
import java.io.*; 

public class PlayerCreation {
     
    private static String playerName = new String (); 
    private static String playerPassword = new String (); 
    private static String lastLoginDate = new String (); 
    private static int score = 0;
    
    public static void createPlayer (){
        System.out.println ("\nOption 2: Creating new player\n");
        
        try 
                {
                    playerInfoFile ("players.dat");        
                }
        
             catch (IOException error)
                {
                    System.out.print ("Error in creating player, please ensure that there is no folder or file named players.dat\n");
                } 
        
    }
    
    public static void playerInfoFile (String args) throws IOException {
       
        String [] listOfNames = new String [10];     
        boolean valid = false; 
        int size = 0; 
        boolean created = false;
        boolean validInput = false; 
        
        try 
        { 
             size = getInfo ("players.dat", listOfNames);       
        }   
        
        catch (FileNotFoundException ex)
        {
              System.out.println ("New players.dat created");   
        }
    
        FileWriter fileOutput = new FileWriter (args, true); 
        
        String tempPassword; 
        Scanner input = new Scanner (System.in);
        
        do 
        {
        System.out.print ("Please enter Player's Name: ");
        playerName = input.nextLine (); 
        
        lastLoginDate = " - "; 
        
        score = 0;
        
        valid = checkValid (playerName, listOfNames, size);
        
        if (valid == true)
        {
            System.out.print ("Please enter Player's Password: ");
            tempPassword = input.nextLine (); 
            playerPassword = Utility.getHash(tempPassword); 
           
            fileOutput.write (playerName + "|");
            fileOutput.write (playerPassword + "|");
            fileOutput.write (lastLoginDate + "|");
            fileOutput.write (score + "|");
            fileOutput.write (System.getProperty ("line.separator"));
            created = true; 
            System.out.print ("Player successfully created!\n");
        }
        else
        {
            System.out.println ("Sorry the name has already been taken. Please try again\n");
            created = false; 
            
        }
        }while (created == false); 
        fileOutput.close(); 
    }

    public static int getInfo (String args, String [] playerInfo ) throws FileNotFoundException 
    {
        Scanner fileInput;
        fileInput = new Scanner (new File (args)); 
               
        String temp;
        String [] dummy = new String [50]; 
        String name; 
        String pass; 
        String lastLogin; 
        String Score;
         
        int counter = 0; 
        
        while (fileInput.hasNextLine())
        {
            temp = fileInput.nextLine ();
            
            dummy= temp.split ("\\|");
        
            playerInfo [counter] = dummy[0];
            
            
            counter++; 
        }
        
        fileInput.close (); 
        
        return counter; 
        
    }

    public static boolean checkValid (String newPlayerName, String [] listOfNames, int size)
    {
        boolean valid = true; 
        for (int i = 0; i < size; i++ )
        {
            if (newPlayerName.equalsIgnoreCase (listOfNames[i]))
                    valid = false;
        }
        
        return valid; 
    }
}
