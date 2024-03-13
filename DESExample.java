import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;

public class DESExample {

    public static void main(String[] args) throws Exception {
        // Key for DES algorithm (8 bytes long)
        String key = "12345678";
        // Plain text to be encrypted
        String plainText = "Hello, DES!";
        
        // Encrypt the plain text
        byte[] encryptedText = encrypt(plainText, key);
        System.out.println("Encrypted Text: " + new String(encryptedText));
        
        // Decrypt the encrypted text
        String decryptedText = decrypt(encryptedText, key);
        System.out.println("Decrypted Text: " + decryptedText);
    }

    // Method to encrypt a string using DES algorithm
    public static byte[] encrypt(String plainText, String key) throws Exception {
        // Create DES cipher instance and initialize it for encryption using the key
        Cipher cipher = Cipher.getInstance("DES");
        SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes(), "DES");
        cipher.init(Cipher.ENCRYPT_MODE, secretKeySpec);
        // Encrypt the plain text
        return cipher.doFinal(plainText.getBytes());
    }

    // Method to decrypt a byte array using DES algorithm
    public static String decrypt(byte[] encryptedText, String key) throws Exception {
        // Create DES cipher instance and initialize it for decryption using the key
        Cipher cipher = Cipher.getInstance("DES");
        SecretKeySpec secretKeySpec = new SecretKeySpec(key.getBytes(), "DES");
        cipher.init(Cipher.DECRYPT_MODE, secretKeySpec);
        // Decrypt the encrypted text
        byte[] decryptedBytes = cipher.doFinal(encryptedText);
        // Convert decrypted bytes to string and return
        return new String(decryptedBytes);
    }
}
