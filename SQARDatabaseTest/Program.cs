using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace SQARDatabaseTest
{
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    struct SQARFileInformation
    {
        uint offset;
        uint size;
        ulong hash;
        string path;
	};

    class PInvoke
    {
        [DllImport("../../../x64/Release/SQARDatabase.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Ansi)]
        private static extern void GetFileNames(uint datPathCount, string[] datPaths, uint dictionaryLineCount, string[] dictionaryEntries, out uint fileInfoCount, out IntPtr fileInfo);

        public static string[] GetFileNames(string[] datPaths, string[] dictionaryEntries)
        {
            IntPtr fileInfo = IntPtr.Zero;
            GetFileNames((uint)datPaths.Length, datPaths, (uint)dictionaryEntries.Length, dictionaryEntries, out uint fileInfoCount, out fileInfo);

            var unmanagedFileInfo = new IntPtr[fileNameCount];
            Marshal.Copy(fileNames, umStringArray, 0, (int)fileNameCount);

            var mStringArray = new string[fileNameCount];
            
            for (uint i = 0; i < fileNameCount; i++)
            {
                var ptr = umStringArray[i];
                mStringArray[i] = Marshal.PtrToStringAnsi(ptr);
                Marshal.FreeCoTaskMem(ptr);
            }

            Marshal.FreeCoTaskMem(fileNames);

            return mStringArray;
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            var dictionary = File.ReadAllLines("../../../qar_dictionary.txt");
            var result = PInvoke.GetFileNames(new string[] { "../../../chunk0.dat" }, dictionary);
            foreach (var path in result)
                Console.WriteLine(path);
            Console.ReadKey();
        }
    }
}
