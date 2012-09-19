import java.io.*;

public class CopyFile
{
	public static void main(String[] args) {
		try {
			FileInputStream fin = new FileInputStream("f.scratch");
			FileOutputStream fout = new FileOutputStream("f.copy");
			int BLOCK_SIZE = 4096 * 64;
			byte block[] = new byte[BLOCK_SIZE];
			while (true) {
				int sz = fin.read(block);
				if (sz <= 0) break;
				fout.write(block, 0, sz);
			}
			fin.close();
			fout.close();
		}
		catch (IOException ioe) {
			ioe.printStackTrace();
		}
	}
}
