global _main          ; Déclaration de la fonction principale du programme.

section .text         ; Section de code du programme.
_main:                ; Point d'entré du programme.
  xor rax, rax ; Ligne 1
  push rax     ; Ligne 2

  mov ah, 125  ; Ligne 3
  mov al, 135  ; Ligne 4
  add ah, al   ; Ligne 5

  mov rbx, 2   ; Ligne 6
  mov rcx, 4   ; Ligne 7
  call Swap    ; Ligne 8

  pop rdx      ; Ligne 9

  mov rax, 0x02000001 ; Numéro de fonction pour la fin du programme.
  xor rdi, rdi        ; Initialisation de la valeur de retour à 0.
  syscall             ; Appel du système d'exploitation.

Swap:          ; Ligne 10
  push rbx     ; Ligne 11
  push rcx     ; Ligne 12
  pop rbx      ; Ligne 13
  pop rcx      ; Ligne 14

  ret          ; Ligne 15
