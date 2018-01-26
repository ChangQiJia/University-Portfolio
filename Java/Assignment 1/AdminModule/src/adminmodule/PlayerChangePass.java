package adminmodule;

import java.util.*; 
import java.io.*; 

public class PlayerChangePass {
    public static void changePlayerPass ()
    {
        System.out.println ("\nOption 4: Reset player's password\n");
        
        try 
                {
                    changePass ("players.dat");        
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
    
    public static void changePass (String args) throws IOException 
    {
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
        String newPass = " ";
        boolean found = false; 
        boolean same = false; 
        
        Scanner fileInput;
        fileInput = new Scanner (new File (args)); 
        
        System.out.print ("Please enter the name of the player you wish to reset the password: ");
        name = input.nextLine();
        
        String hashPass = " ";
        hashPass = Utility.getHash ("123456");
         
        String temp;
        String [] dummy = new String [10]; 
        
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
                fileOutput.write (playerName[i] + "|");
                fileOutput.write (hashPass + "|");
                fileOutput.write (lastLoginDate[i] + "|");
                fileOutput.write (score[i] + "|");
                fileOutput.write (System.getProperty ("line.separator"));
                found = true; 
                System.out.println (playerName[i] + " password resetted to 123456\n");
            }
            
        }

        fileOutput.close (); 
 
        if (found == false)
        {
            System.out.println ("Sorry, the player you are looking for is not available");
        }  
    }
}
