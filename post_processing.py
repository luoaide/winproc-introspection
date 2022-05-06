file = open("handles.txt", "r")

unique_handles = set()

for line in file:
  handle = line.strip()
  unique_handles.add(handle)
  
file.close()

print("Valid handles:")
for handle in unique_handles:
  print(handle)
  
  
