defmodule InsertionSort do
  @moduledoc """
  #Insertion_Sort 

  This is writen in Elixir -> http://elixir-lang.org/getting_started/1.html

  Things you need to know:
  - The last statement is automatically returned
  - functions with the same name are the same function they match what's in 
 their argument list


  """


  @doc """
  Will insert an item in the proper part of a list (assuming sorted list)
  """
  def insert(item, []) do
    [item]
  end
  def insert(item, list=[head|tail]) do
    if item <= head do
      [item | list] # finally insert it in proper place
    else
      [head | insert(item, tail)]  # Recursively move it one spot right
    end
  end


  @doc """
  This will do an Insertion Sort
  """
  def sort([]) do
    []
  end
  def sort([head|tail]) do
    insert(head, sort(tail))
  end



  def test(list) do
    IO.puts "Origional list"
    IO.puts Enum.join(list, " ")

    sortedlist = InsertionSort.sort(list)
    IO.puts ""

    IO.puts "Sorted list"
    IO.puts Enum.join(sortedlist, " ")
  end

end


InsertionSort.test([9,4,0,12, 1.9, 1, 12, 134])

