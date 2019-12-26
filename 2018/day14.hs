module Main where

import Prelude hiding (take, drop)
import Control.Monad.Trans.State.Lazy
import Control.Monad.ST

import Data.Word (Word8)
import Data.Array.ST

--                 Score                  len  elf1 elf2
data Board s = Board (STUArray s Int Word8) Int  Int  Int


decorate_index :: Int -> Int -> Int -> (Int, Int) -> String
decorate_index len elf1 elf2 (index, score)
    | elf1 == index = "(" ++ show score ++ ")"
    | elf2 == index = "[" ++ show score ++ "]" 
    | len - 1 == index = " " ++ show score
    | otherwise = " " ++ show score ++ " "


--instance Show Board  where
--    show (Board board len elf1 elf2) = concat $ map (decorate_index len elf1 elf2) iboard
--       where iboard = zip [0..] board

update_elfs :: State Board ()
update_elfs = do
    (Board board len elf1 elf2) <- get
    let new_elf e = (e + (board !! e) + 1) `mod` len
    put (Board board len (new_elf elf1) (new_elf elf2))

new_recipes :: State Board Int
new_recipes = do
    (Board board len  elf1 elf2) <- get
    let elf_sum = (board !! elf1) + (board !! elf2)
    if elf_sum >= 10
        then do
            put (Board (board ++ [elf_sum `div` 10, elf_sum `mod` 10])
                       (len + 2) elf1 elf2)
            update_elfs
            return 2

        else do
            put (Board (board ++ [elf_sum]) (len + 1) elf1 elf2)
            update_elfs
            return 1

make_nr_recipes :: Int -> State Board ()
make_nr_recipes recipes_left =
    if recipes_left <= 0 then return ()
                         else do
                              amnt_new_recipes <- new_recipes
                              make_nr_recipes (recipes_left - amnt_new_recipes)

part1 :: Int -> [Int]
part1 nr_recipes = take 10 $ drop nr_recipes $ result_board
    where (Board result_board _ _ _) = execState (make_nr_recipes (nr_recipes + 10)) initial_board


initial_board :: (ST s) => Board s
initial_board = do
    board_arr <- newArray (0, 10000000) 0
    writeArray board_arr 0 3
    writeArray board_arr 1 7
    (Board board_arr 2 0 1)

main :: IO ()
main = print $ part1 409551
