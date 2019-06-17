{-
MIT License

Copyright (c) 2019 Alexander Hill

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-}

import Data.Binary
import Data.List
import Foreign.C.String
import System.Directory
import System.Info
import System.IO

driveList = [] :: [IO Handle]

foreign export ccall closeDisk :: Int -> IO ()
closeDisk :: Int -> IO ()
closeDisk number = hClose $ driveList !! number

getDiskName :: Int -> IO FilePath
getDiskName number = do
  case os of
    "linux" -> do
      let drives = filter isGUID $ listDirectory "/dev/disk/by-uuid"
      return ("/dev/disk/by-uuid/" ++ (drives !! number)) :: IO FilePath
    _ -> return "" :: IO FilePath

isGUID :: String -> Bool
isGUID name = do
  --

foreign export ccall openDisk :: Int -> IO Int
openDisk :: Int -> IO Int
openDisk number = do
  let handle = openBinaryFile (getDiskName number) ReadMode
  return $ (length (driveList ++ [handle])) - 1

foreign export ccall readSector :: Int -> Int -> IO CString
readSector :: Int -> Int -> IO CString
readSector number lba = do
  --
