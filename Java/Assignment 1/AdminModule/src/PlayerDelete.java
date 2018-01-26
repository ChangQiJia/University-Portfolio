

import java.util.*; 
import java.io.*; 

public class PlayerDelete {
    public static void deletePlayer ()
    {
        System.out.println ("\nOption 3: Deleting new player\n");
        
        try 
                {
                    playerDeletion ("players.dat");        
                }
             
             catch (FileNotFoundException ex)
                {
                   System.out.print ("File players.dat cannot be found. Please create the file using Option 2. Create a player\n");
                }
             catch (IOException error)
                {
                    System.out.print ("Error in deleting player, please ensure that there is no folder named players.dat\n");
                } 
    }

    public static void playerDeletion (String args) throws IOException {
       
        Scanner input = new Scanner (System.in);
        String tempScore; 
        int counter = 0; 
        
        String [] playerName;
        playerName = new String [10]; 
        
        String [] playerPassword;
        playerPassword = new String [10];
        
        String [] lastLoginDate;
        lastLoginDate = new String [10];
        
        int [] score;
        score = new int [10];                
                
        String name = " "; 
        boolean found = false; 
        
        Scanner fileInput;
        fileInput = new Scanner (new File (args)); 
        
        
        System.out.print ("Please enter the name of the player you wish to delete: ");
        name = input.nextLine();
        System.out.print ("\n");
        
       
        String temp;
        String [] dummy = new String [50]; 

        
       while (fileInput.hasNextLine())
        {
            temp = fileInput.nextLine ();
            
            dummy = temp.split ("\\|");
            playerName[counter] = dummy[0];
            playerPassword[counter] = dummy[1]; 
            lastLoginDate[counter] = dummy[2]; 
            tempScore = dummy[3];
            score[counter] = Integer.parseInt (tempScore);
             
            counter++;
        } 
        
        fileInput.close (); 
        FileWriter fileOutput = new FileWriter ("players.dat"); 
        
        for (int i = 0; i < counter ; i++ )
        {    
            if (!name.equalsIgnoreCase(playerName[i]))
            {
                fileOutput.write (playerName[i] + "|");
                fileOutput.write (playerPassword[i] + "|");
                fileOutput.write (lastLoginDate[i] + "|");
                fileOutput.write (score[i] + "|");
                fileOutput.write (System.getProperty ("line.separator"));
            }
            
            else 
            {
                found = true;
                System.out.println ("Player succesfully deleted\n");
            }
            
        }

        fileOutput.close (); 
 
        
        if (found == false)
        {
            System.out.println ("Sorry, the player you are looking for is not available\n");
        }  
        
        
    }
}
