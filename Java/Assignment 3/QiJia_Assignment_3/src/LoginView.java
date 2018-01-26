/*
* CSCI213 Assignment 3
* --------------------------
* File name: LoginView.java
* Author: Chang Qi Jia
* Student Number: 5280618
* Description: View to show before succesful log in
*/

import javax.swing.*; 
import java.awt.*; 
import java.util.*; 
import java.awt.event.*;

public class LoginView extends JFrame{
    
    private ViewController vc; 
    private JPanel loginScreen;
    private JLabel password, username; 
    private JTextField usernameBox; 
    private JPasswordField passwordBox; 
    private JButton loginButton; 
    private JFrame frame; 
    private JFrame tryFrame; 
    
    public LoginView (ViewController vc)
    {
        super ("User Login");
        this.vc = vc; 
        
        
        loginScreen = new JPanel ();
        loginScreen.setPreferredSize (new Dimension (275,100));
        
        username = new JLabel ("Username");
        password = new JLabel ("Password");
        
        usernameBox = new JTextField (15);
        passwordBox = new JPasswordField (15); 
        
        loginButton = new JButton ("Login");
        
        loginButton.addActionListener (new LoginActionListener ());
        
        loginScreen.add(username);
	loginScreen.add(usernameBox);
	loginScreen.add(password);
        loginScreen.add(passwordBox);
        loginScreen.add(loginButton);
	add(loginScreen);
	pack();
          
    }
    
     public LoginView ()
    {
        super ("Fishing Game Login");
        this.vc = vc; 
        
        loginScreen = new JPanel (); 
        loginScreen.setPreferredSize (new Dimension (275,100));
        username = new JLabel ("Username");
        password = new JLabel ("Password");
        
        usernameBox = new JTextField (15);
        passwordBox = new JPasswordField (15); 
        
        loginButton = new JButton ("Login");
        
        loginButton.addActionListener (new LoginActionListener ());
        
        loginScreen.add(username);
	loginScreen.add(usernameBox);
	loginScreen.add(password);
        loginScreen.add(passwordBox);
        loginScreen.add(loginButton);
	add(loginScreen);
	pack();
           
    }
    
    private class LoginActionListener implements ActionListener{
    
        public void actionPerformed(ActionEvent event){
                
            String username = usernameBox.getText();
            String password = new String (passwordBox.getPassword());
            
            vc.loginCallback(username, password);
        }
    }
    
    public static void main (String [] args)
    {
        LoginView lv = new LoginView ();
        
        lv.setPreferredSize (new Dimension (275,100)); 
        lv.setDefaultCloseOperation (EXIT_ON_CLOSE);
        
        lv.setVisible (true); 
    }
    
    public void printMessage (String msg)
    {
        frame = new JFrame ("Login");
        JPanel msgPanel = new JPanel (); 
        msgPanel.setPreferredSize (new Dimension (400,125));
                
        JLabel toPrint = new JLabel (msg);
        toPrint.setPreferredSize (new Dimension (400,30));
        toPrint.setHorizontalAlignment (SwingConstants.CENTER);
                
        JButton okay = new JButton ("Okay");
        okay.setPreferredSize (new Dimension (100,30));
        okay.addActionListener (new okayButtonListener ());
                
        msgPanel.add (toPrint); 
        msgPanel.add (okay); 
                
        frame.setPreferredSize (new Dimension (500,125));
        frame.add (msgPanel);
        frame.pack(); 
        frame.setVisible (true); 
    }
   
    private class okayButtonListener implements ActionListener{
        
        public void actionPerformed (ActionEvent e)
        {
            frame.setVisible (false); 
            vc.welcomeMessageCallBack();
        }
    }
    
    public void tryAgain () 
    {
        tryFrame = new JFrame ("Try Again?");
        JPanel panel = new JPanel (); 
        panel.setPreferredSize (new Dimension (275, 100));
        
        JLabel msg = new JLabel ("Login Failed! Would you like to try again?");
        msg.setPreferredSize (new Dimension (265, 35));
        msg.setHorizontalAlignment (SwingConstants.CENTER);
        
        JButton yes = new JButton ("Yes");
        yes.setPreferredSize (new Dimension (100,30));
        
        JButton no = new JButton ("No");
        no.setPreferredSize (new Dimension (100,30));
        
        yes.addActionListener (new yesListener ());
        no.addActionListener (new noListener ()); 
        
        panel.add (msg); 
        panel.add (yes); 
        panel.add (no); 
        
        tryFrame.add (panel); 
        tryFrame.pack(); 
        tryFrame.setVisible (true); 
    }
    
    private class yesListener implements ActionListener {
        public void actionPerformed (ActionEvent e)
        {
            tryFrame.setVisible (false); 
            vc.tryAgainCallBack(); 
        }
    }
    
    private class noListener implements ActionListener {
        public void actionPerformed (ActionEvent e)
        {
            System.exit (0); 
        }
    }
}

