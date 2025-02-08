#!/usr/bin/env fish
stow -t (dirname "$(kpsewhich -var-value TEXMFHOME)") texmf-stow
