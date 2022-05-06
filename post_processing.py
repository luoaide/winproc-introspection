file = open("handles.txt", "r")

unique_handles = set()

for line in file:
  handle = line.strip()
  unique_handles.add(handle)
  
file.close()

list_of_handles = list(unique_handles)
list_of_handles.sort()

print("Valid handles:")
for handle in list_of_handles:
  print(handle)
