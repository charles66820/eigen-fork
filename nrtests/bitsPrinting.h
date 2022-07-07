#ifndef EIGEN_MIPP_BITS_PRINTING_H
#define EIGEN_MIPP_BITS_PRINTING_H

std::string printBytes(u_char* bytes, size_t nbBytes) {
  std::stringstream res;
  for (size_t nbByte = 0; nbByte < nbBytes; nbByte++) {
    for (int i = 7; i >= 0; i--)
      res << ((bytes[nbByte] & (1 << i)) ? "1" : "0");
    res << " ";
  }
  return res.str();
}

std::string printVecBits(std::string str, const __m128& var) {
  std::stringstream res;
  res << str << " bits = ";
  res << "{ ";
  res << printBytes((u_char*)&var[0], sizeof(float));
  res << "|";
  res << printBytes((u_char*)&var[1], sizeof(float));
  res << "}\n";
  return res.str();
}

std::string printVecBits(std::string str, const __m256& var) {
  std::stringstream res;
  res << str << " bits = ";
  res << "{ ";
  res << printBytes((u_char*)&var[0], sizeof(float));
  res << "|";
  res << printBytes((u_char*)&var[1], sizeof(float));
  res << "|";
  res << printBytes((u_char*)&var[2], sizeof(float));
  res << "|";
  res << printBytes((u_char*)&var[3], sizeof(float));
  res << "}\n";
  return res.str();
}

std::string printVecsBits(const __m256& va, const __m256& vb) {
  return "\n" + printVecBits("new", va) + printVecBits("old", vb);
}
#endif  // EIGEN_MIPP_BITS_PRINTING_H